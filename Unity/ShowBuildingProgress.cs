using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

/// <summary>
/// 건물이 지어지는 상태를 표시해준다.
/// </summary>
public class ShowBuildingProgress : MonoBehaviour
{
    public Texture2D background;
    //public Texture2D fillTexture;
    public BuildingMENU buildingToPlace;
    //public GameObject buildTimer;
    //SpawnBuildings spawnBuildings;
    float width = 90f;
    float height = 10f;
    float buildTime;
    int remaining;


    //float startTime;

    private void Awake()
    {
        //spawnBuildings = GameObject.FindObjectOfType<SpawnBuildings>();
        //this.buildingToPlace = spawnBuildings.buildingToPlace;
        remaining = (int)buildingToPlace.buildTime;
    }
    private void Start()
    {
        // startTime = Time.time;
        buildTime = buildingToPlace.buildTime;
        //buildTimer = Instantiate(buildTimer, Input.mousePosition, Quaternion.identity);

    }
    IEnumerator Timer()
    {
        for (int i = 0; i < remaining; remaining--)
        {
            yield return new WaitForSeconds(1f);
        }
    }
    public void OnGUI()
    {
        //     // GUI.BeginGroup(new Rect(0, 0, width * Mathf.Clamp01((Time.time - startTime) / buildTime), height));
        //     // Debug.Log($"startTime: {startTime}");
        //     // GUI.DrawTexture(new Rect(0, 0, width, height), fillTexture);

        //     // GUI.EndGroup();


        if (!EventSystem.current.IsPointerOverGameObject())
        {
            Vector3 screenPos = Camera.main.WorldToScreenPoint(transform.position);
            Vector2 guiPos = new Vector2(screenPos.x - (width / 2), Screen.height - screenPos.y - height * 4);

            GUI.color = Color.red;
            GUI.BeginGroup(new Rect(guiPos, new Vector2(width, height)));
            GUI.DrawTexture(new Rect(0, 0, width, height), background);
            GUI.EndGroup();

            GUI.contentColor = Color.black;
            GUI.Label(new Rect(guiPos.x + width / 2, guiPos.y - height / 2, width, 75), remaining.ToString());
            //Debug.Log($"buildTime: {buildTime}");
            if (remaining == 0)
            {
                // gameObject.GetComponent<ShowBuildingProgress>().enabled = false;
                this.enabled = false;

                if (gameObject.name == "tempBuilding")
                {
                    gameObject.name = buildingToPlace.prefabName;
                    if (gameObject.name == "mana_well_upg_01(Clone)")
                    {
                        gameObject.GetComponent<ManaWell>().enabled = true;
                    }
                    else if (gameObject.name == "gold_mine_upg_01(Clone)")
                    {
                        gameObject.GetComponent<GoldMine>().enabled = true;
                    }
                    else if(gameObject.name == "gold_storage_upg_01(Clone)")
                    {
                        gameObject.GetComponent<GoldStorage>().enabled = true;
                    }
                    else if(gameObject.name == "mana_storage_upg_01(Clone)")
                    {
                        gameObject.GetComponent<ManaStorage>().enabled = true;
                    }
                }
            }
        }
    }


    private void OnEnable()
    {
        StartCoroutine(Timer());
    }
    private void Update()
    {
        //buildTime = buildingToPlace.buildTime;
    }
}

/*
    Mathf.Clamp01 : num값을 강제로 0에서 1범위의 값으로 집어넣는데 사용함.
    Mathf.Ceil : 올림

    GUI.BeginGroup
    GUI.EndGroup
        참조:https://docs.unity3d.com/kr/530/ScriptReference/GUI.BeginGroup.html
*/