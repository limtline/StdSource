using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// 건물 배치 가이드 타일의 정보를 갖고 있다.
/// </summary>
[RequireComponent(typeof(MeshCollider))]
//[RequireComponent(typeof(Rigidbody))]

public class productionTile : MonoBehaviour
{
    #region Inspector Variables
    [Tooltip("배치 가능함을 알리는 타일의 색")]
    [SerializeField] Color green;

    [Tooltip("배치 불가능함을 알리는 타일의 색")]
    [SerializeField] Color red;

    [Tooltip("복사할 Material BuildingProductionTile")]
    [SerializeField] Material mat;

   [Tooltip("캐스팅할 레이어")]
    [SerializeField] LayerMask collisionLayer;

    // 타일의 콜라이더가 어떤 오브젝트의 콜라이더에 닿았는지 확인할 변수
    public bool colliding { get; private set; }
    #endregion Inspector Variables

    private void Awake()
    {
        gameObject.GetComponent<Renderer>().material.CopyPropertiesFromMaterial(mat);
    }

    // Start is called before the first frame update
    void Start()
    {
        SetColor(green);
    }

    private void Update() {
       // CollidingCheck();
    }

    void SetColor(Color c)
    {
        gameObject.GetComponent<MeshRenderer>().material.SetColor("_TintColor", c);
    }

     void OnTriggerEnter(Collider other) {
         //만약 레이어마스크가 게임오브젝트의 레이어와 같다면
        if(collisionLayer == (collisionLayer | (1<<other.gameObject.layer)))
        {
            // 콜라이더가 있는 게임오브젝트 트랜스폼의 최상위 오브젝트에 인스턴스ID가 해당 트랜스폼 최상의 오브젝트의 ID가 아니면,
            if(other.gameObject.transform.root.gameObject.GetInstanceID() != transform.root.gameObject.GetInstanceID())
            {
                SetColor(red);    // red가 맞나??
                colliding = true;
            }
        }
    }

     void OnTriggerExit(Collider other) {
        if(collisionLayer == (collisionLayer | (1<<other.gameObject.layer)))
        {
            SetColor(green);      // 얘는 green ?
            colliding = false;
        }
    }
    
}

/*
    RequireComponent 란?
    요구되는 컴포넌트를 종속성으로 자동으로 추가해준다.
        RequireComponent를 사용하는 스크립트를 GameObject에 추가하면 필요한 Component가 GameObject에 자동으로 추가된다.
        참조: https://artiper.tistory.com/105

    CopyPropertiesFromMaterial 란?
        Material의 특성 값을 복사한다.

    LayerMask 란?
        LayerMask는 인스펙터에서 팝업 메뉴를 보이도록 해준다.
        레이 캐스팅에 대해서 게임 오브젝트를 선택적으로 필터링할 때 사용할 수 있다.
        참조 : https://docs.unity3d.com/kr/530/ScriptReference/LayerMask.html
*/
