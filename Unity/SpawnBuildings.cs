using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using UnityEngine.UI;
/// <summary>
/// 건물을 배치해주는 데이터
/// </summary>
public class SpawnBuildings : MonoBehaviour
{
    [SerializeField] GameObject productionTile;         // 타일
    [SerializeField] LayerMask layer;
    [SerializeField] GraphicRaycaster uiRaycaster;      // 버튼
    public BuildingMENU buildingToPlace;      // 프리팹을 지정한 스크립팅오브젝트

    // [SerializeField] Texture2D background;
    // [SerializeField] Texture fillTexture;
    // float width = 90f;
    // float height = 10f;
    // float startTime;
    float buildTime;
    [SerializeField] GameObject buildTimer;

    GameObject parent;
    GameObject tobe;
    public GameObject currentSpawnedBuilding;                  // 건물을 넣을 빈 게임 오브젝트
    RaycastHit hit;
    List<productionTile> activeTiles;                   // 타일을 리스트로 넣을거임
    GameObject activeTilesParent;                       // 타일을 담을 부모 오브젝트를 만들어줄거다
    GameObject buildingEffectPrefab;

    public ButtonLockController buttonLockController;
    GoldStorage goldStorage;
    ManaStorage manaStorage;

    public Text txtWarning;


    private void Awake()
    {
        activeTiles = new List<productionTile>();
        parent = GameObject.FindWithTag("HOME");
        tobe = GameObject.FindWithTag("TOBE");
        buildingEffectPrefab = Resources.Load<GameObject>("CameraShakeFX/Demo/Particles/build");
    }
    // Start is called before the first frame update
    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        goldStorage = GameObject.FindObjectOfType<GoldStorage>();
        manaStorage = GameObject.FindObjectOfType<ManaStorage>();

        if (currentSpawnedBuilding)
        {
            if (Input.GetMouseButtonDown(0))
            {
                // 만약 마우스 포지션에 레이를 쏘지 않았으면,
                if (!PlacementHelpers.RaycastFromMouse(out hit, layer))
                    return;

                // 게임오브젝트의 위치를 레이저쏜 위치로 가져온다
                //currentSpawnedBuilding.transform.position = hit.point - new Vector3(0, 4, 0);

                if (goldStorage.myGold < buildingToPlace.gold || manaStorage.myMana < buildingToPlace.mana)
                {
                    Debug.Log("재화가 부족합니다.");
                    Destroy(currentSpawnedBuilding);
                    txtWarning.rectTransform.position = Input.mousePosition;
                    if (goldStorage.myGold < buildingToPlace.gold)
                    {
                        txtWarning.text = "Gold가 부족합니다.";
                    }
                    else if (manaStorage.myMana < buildingToPlace.mana)
                    {
                        txtWarning.text = "Mana가 부족합니다.";
                    }
                    StartCoroutine(TextTimer());
                }
                else
                {
                    // 건물을 지을수 있으면,
                    if (CanPlaceBuilding())
                    {
                        currentSpawnedBuilding.GetComponent<ShowBuildingProgress>().enabled = true;
                        PlaceBuilding();    // 지어라

                        switch (buildingToPlace.prefabName)
                        {
                            case "gold_storage_upg_01(Clone)":
                                buttonLockController.goldStorageCount++;
                                break;
                            case "gold_mine_upg_01(Clone)":
                                buttonLockController.goldMineCount++;
                                break;
                            case "mana_storage_upg_01(Clone)":
                                buttonLockController.manaStorageCount++;
                                break;
                            case "mana_well_upg_01(Clone)":
                                buttonLockController.manaWellCount++;
                                break;
                        }

                        goldStorage.myGold -= buildingToPlace.gold;
                        manaStorage.myMana -= buildingToPlace.mana;
                    }
                }
            }

            if (Input.GetMouseButtonDown(1))
                Destroy(currentSpawnedBuilding);
        }
    }

    IEnumerator TextTimer()
    {
        yield return new WaitForSeconds(2f);
        txtWarning.text = "";
    }

    void FixedUpdate()
    {
        if (currentSpawnedBuilding)

            // 만약 마우스 포지션에 레이를 쐈다면,
            if (PlacementHelpers.RaycastFromMouse(out hit, layer))
            {
                // 레이저 point의 vector3값에 게임오브젝트를 위치시켜라
                //currentSpawnedBuilding.transform.position = new Vector3(0, 4, 0);
                // Vector2 tmp = new Vector2(currentSpawnedBuilding.transform.position.x, currentSpawnedBuilding.transform.position.z);

                int tmpX = ((int)currentSpawnedBuilding.transform.position.x);
                int tmpZ = ((int)currentSpawnedBuilding.transform.position.z);
                int hitX = ((int)hit.point.x);
                int hitZ = ((int)hit.point.z);

                for (int i = 1; ; tmpX += 2 * i)
                {
                    if (tmpX > hitX)
                        i = -1;
                    if (tmpX == hitX || tmpX + 1 == hitX || tmpX - 1 == hitX)
                        break;
                }

                for (int i = 1; ; tmpZ += 2 * i)
                {
                    if (tmpZ > hitZ)
                        i = -1;
                    if (tmpZ == hitZ || tmpZ + 1 == hitZ || tmpZ - 1 == hitZ)
                        break;
                }

                currentSpawnedBuilding.transform.position = new Vector3(tmpX, 4, tmpZ);

                //currentSpawnedBuilding.transform.position = new Vector3(hit.point.x, 4, hit.point.z);
                //currentSpawnedBuilding.transform.Translate(new Vector3(hit.point.x, 4, hit.point.z));

            }
    }

    bool CanPlaceBuilding()
    {
        // UI 버튼이 눌렸나
        if (PlacementHelpers.IsButtonPressed(uiRaycaster))
            return false;

        // 리스트에 담긴 만큼 증가
        for (int i = 0; i < activeTiles.Count; i++)
            if (activeTiles[i].colliding)
                return false;
        return true;
    }

    void PlaceBuilding()
    {
        ClearGrid();
        StartCoroutine(BeginBuilding());
    }

    void ClearGrid()
    {
        // 타일을 삭제하고
        Destroy(activeTilesParent);
        // 리스트에 담은 것도 삭제한다. (람다식임)
        activeTiles.RemoveAll(i => i);
    }

    IEnumerator BeginBuilding()
    {
        currentSpawnedBuilding.transform.SetParent(parent.transform);

        // 벡터를 만들어 게임 오브젝트의 위치를 담고,
        Vector3 pos = currentSpawnedBuilding.transform.position;
        // 빈 게임 오브젝트를 만들어 그 오브젝트를 담고
        GameObject instance = currentSpawnedBuilding;
        BoxCollider col = instance.GetComponent<BoxCollider>();

        instance.AddComponent<Rigidbody>();
        instance.GetComponent<Rigidbody>().useGravity = false;
        instance.GetComponent<Rigidbody>().isKinematic = true;

        if (col.size == new Vector3(8, 4, 8))
            col.size = new Vector3(6, 4, 6);

        // 그 오브젝트는 비워둬라
        currentSpawnedBuilding = null;

        RaycastHit hit;
        // 만약 레이를 쐈다면
        if (PlacementHelpers.RaycastFromMouse(out hit, layer))
            // 위치는 쏜곳으로
            pos = hit.point;

        // 빈 게임 오브젝트에 스크립팅 오브젝트에 들어있는 프리뷰 프리팹을 넣고, 위치를 가져온다
        //GameObject obj = Instantiate(buildingToPlace.buildingPreviewPrefab, pos, Quaternion.identity);

        // startTime = Time.time;
        // buildTime = buildingToPlace.buildTime;
        // OnGUI();

        // 스크립팅 오브젝트에서 설정한 빌드 시간까지 기다려라
        Debug.Log("Waited " + buildingToPlace.buildTime);
        GameObject tmpEffect = Instantiate(buildingEffectPrefab, Camera.main.ScreenToWorldPoint(Input.mousePosition) - new Vector3(0, 4, 0), Quaternion.identity);
        yield return new WaitForSeconds(buildingToPlace.buildTime);
        Destroy(tmpEffect);

        // 렌더러를 활성화 시켜서 화면에 보이게 하자 
        PlacementHelpers.ToggleRenderers(instance, true);
        //Destroy(obj);
    }

    void FillRectWihtTiles(Collider col)
    {
        if (activeTilesParent)
            return;

        // 렉탱글 위치를 지정했던거로 가져온다
        Rect rec = PlacementHelpers.MakeRectOfCollider(col);

        // 여기서 부턴 타일이 어디로 연결될지 정해주고.
        float fromX = rec.position.x;
        //float toX = (rec.position.x + rec.width) * col.gameObject.transform.localScale.x;
        float toX = (rec.position.x + rec.width);
        float fromZ = rec.position.y;
        //float toZ = (rec.position.y + rec.height) * col.gameObject.transform.localScale.z;
        float toZ = (rec.position.y + rec.height);

        // 빈게임 오브젝트를 하나 만듬
        GameObject parent = new GameObject("PlacementGrid");
        // 방금 만든 오브젝트를 최상위 부모로 지정한다
        parent.transform.SetParent(col.gameObject.transform);
        //parent.transform.SetParent(col.gameObject.transform.root);

        // 부모가 된 오브젝트의 포지션을 월드방향 벡터를 로컬 위치로 바꾼다. << 이거때문에 하늘에서 생기는것 같다는 추측
        parent.transform.position = col.gameObject.transform.InverseTransformPoint(new Vector3(0, 0.02f, 0));

        // 타일이 잘 연결 되도록 
        for (float i = -toX / 2; i <= toX / 2; i += productionTile.transform.localScale.x)
        {
            for (float j = -toZ / 2; j <= toZ / 2; j += productionTile.transform.localScale.y)
            {
                // 연결될 타일을 생성해주고
                GameObject tile = Instantiate(productionTile);
                // 부모 오브젝트의 자식으로 지정해주고
                tile.transform.SetParent(parent.transform);
                // 연결된 타일의 위치 설정해 주고,
                tile.transform.position = new Vector3(i, parent.transform.position.y, j);
                // 이제 진짜 타일을 만들어서 화면에 보이도록!
                activeTiles.Add(tile.GetComponent<productionTile>());
            }
        }
        // 만든 타일을 담아줬다
        activeTilesParent = parent;
    }

    public void SpawnBuilding(BuildingMENU building)
    {
        if (currentSpawnedBuilding)
            return;

        // 추가함 @@ 상점 판넬 닫히도록 
        uiRaycaster.transform.Find("pnlUI").gameObject.SetActive(false);
        //uiRaycaster.transform.Find("pnlStore").gameObject.SetActive(false);

        // 빈 오브젝트에 스크립팅 오브젝트의 프리팹을 연결해주고
        currentSpawnedBuilding = Instantiate(building.buildingPrefab);
        currentSpawnedBuilding.transform.SetParent(tobe.transform);

        // 스크립팅 오브젝트의 프리뷰프리팹을 바꿔줄건데 이걸로 바꿔주는게 맞는지 모르겠다
        //buildingToPlace.buildingPreviewPrefab = building.buildingPrefab;    // buildingToPlace로 해도 되고 building으로 해도 되고
        // 가져왔으면 프리팹을 화면에 그려준다
        PlacementHelpers.ToggleRenderers(currentSpawnedBuilding, true);
        // 자식들의 콜라이더도 담고 .. 근데 자식들한텐 콜라이더가 없음, 쿼드 빼고.
        // 수정 1번 
        //Collider[] cols = currentSpawnedBuilding.GetComponentsInChildren<Collider>();
        Collider col = currentSpawnedBuilding.GetComponent<Collider>();
        // if(cols.Length>0)
        //     FillRectWihtTiles(cols[0]);
        FillRectWihtTiles(col);

        buildingToPlace = building;

        currentSpawnedBuilding.name = "tempBuilding";

        // if (manaStorage.myMana > buildingToPlace.mana || goldStorage.myGold > buildingToPlace.gold)
        // {
        //       switch (currentSpawnedBuilding.gameObject.name)
        //     {
        //         case "gold_storage_upg_01(Clone)":
        //             buttonLockController.goldStorageCount++;
        //             break;
        //         case "gold_mine_upg_01(Clone)":
        //             buttonLockController.goldMineCount++;
        //             break;
        //         case "mana_storage_upg_01(Clone)":
        //             buttonLockController.manaStorageCount++;
        //             break;
        //         case "mana_well_upg_01(Clone)":
        //             buttonLockController.manaWellCount++;
        //             break;
        //     }
        // }
    }
}
