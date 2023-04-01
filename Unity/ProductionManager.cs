using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

/// <summary>
/// 건물 배치를 위한 스크립트.
/// </summary>
public class ProductionManager : MonoBehaviour
{
    #region Inspector Variables
    [SerializeField] GameObject productionTile;

    [Tooltip("ScriptableObject")]
    [SerializeField] BuildingMENU scriptableOBJ;

    [SerializeField] GraphicRaycaster canvas;

    public Transform trans;
    #endregion Inspector Variables

    #region Instance Object
    List<productionTile> activeTiles;
    GameObject activeTilesParent;
    public GameObject currentSpawnedBuilding;
    Vector3 screenCenter;
    Ray ray, hitray;
    RaycastHit hit;
    //Transform trans;

    #endregion Instance Object

    private void Awake()
    {
        activeTiles = new List<productionTile>();
        //trans.position = screenCenter;
    }

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        ray.origin = trans.position;

        int lMask = 1 << LayerMask.NameToLayer("Tile");

        if(currentSpawnedBuilding == null)
        {
            ray.direction = trans.TransformDirection(Vector3.forward);
            if(Physics.Raycast(ray,out hit, Mathf.Infinity))
                screenCenter = hit.point;
        }
        else
        {
            if(Input.GetMouseButtonDown(0))
            {
                ray = Camera.main.ScreenPointToRay(Input.mousePosition);
                if(Physics.Raycast(ray, out hit, Mathf.Infinity, lMask))
                {
                    if(hit.collider.tag == "Tile")
                    {
                        hit.transform.position=hit.point;
                    }
                }
            }
        }
    }

    public void ProductionBuilding()
    {
        currentSpawnedBuilding = Instantiate(productionTile, screenCenter+ Vector3.up * 0.01f, Quaternion.Euler(90, 0, 0));
        currentSpawnedBuilding.tag = "Tile";

    }
}

/*
    GraphicRaycaster 란?
    GraphicRaycaster는 Canvas에 Raycast하는데 사용한다.
    Raycaster는 Canvas의 모든 Graphic를 감시하여 그 중 하나에 충돌했는지 여부를 결정한다.

    참조: https://docs.unity3d.com/kr/2020.3/Manual/script-GraphicRaycaster.html
*/