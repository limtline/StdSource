using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;

public class CameraCtrl : MonoBehaviour
{
    // 카메라 이동
    Vector2 prePos; // 첫 터치 위치
    Vector2 nowPos; // 현재 터치 위치 (드래그 위치)
    Vector3 movePos; // 첫 터치에서 드래그 거리

    // 카메라 줌
    Vector3 prePosA; // 첫번째 손가락의 첫 터치 위치
    Vector3 prePosB; // 두번째 손가락의 첫 터치 위치
    private float prePosMag; // 첫번째와 두번째 손가락의 첫 터치간의 사이
    private float nowPosMag; // 현재 손가락들의 터치간의 사이
    private float touchPosMag; // 첫 터치간의 사이와 현재 터치간의 사이의 사이값
    private float zoomSpeed = 0.05f; // 줌 속도
    
    // 오브젝트 선택
    Ray ray; // Ray 정보를 담기 위한 객체
    RaycastHit hitInfo; // Ray충돌 정보를 담기 위한 객체

    public GameObject btnTrain;
    public GameObject pnlBuildingInfo; // 건물 기능 UI 판넬
    private bool isObjTouch = false;


    void Awake()
    {
    }

    // Start is called before the first frame update
    void Start()
    {
    }

    void Update()
    {
        CheckObject();
        Debug.DrawRay(ray.origin, ray.direction * 100.0f, Color.red);
    }

    void LateUpdate()
    {
        CameraMove();
        CameraBorder();
    }

    void CheckObject()
    {
        if (Input.touchCount > 0)
        {
            Touch touch = Input.GetTouch(0);
            if (touch.phase == TouchPhase.Began)
            {
                ray = Camera.main.ScreenPointToRay(touch.position);
                if (Physics.Raycast(ray, out hitInfo, 150.0f))
                {
                    if (hitInfo.collider.tag == "BUILDING")
                    {
                        isObjTouch = true;
                    }
                }
            }
            if (touch.phase == TouchPhase.Moved)
            {
                isObjTouch = false;
            }
            if (touch.phase == TouchPhase.Ended)
            {
                ray = Camera.main.ScreenPointToRay(touch.position);
                if (Physics.Raycast(ray, out hitInfo, 150.0f))
                {
                    if (isObjTouch && hitInfo.collider.tag == "BUILDING")
                    {
                        pnlBuildingInfo.SetActive(true);
                        
                        if (hitInfo.collider.gameObject.name == "barrack_upg_01" ||
                            hitInfo.collider.gameObject.name == "barrack_upg_01(Clone)")
                            btnTrain.SetActive(true);
                        else
                            btnTrain.SetActive(false);
                    }
                    else
                    {
                        pnlBuildingInfo.SetActive(false);
                    }
                }
            } 
        }
    }

    void CameraMove()
    {
        // 카메라 줌
        if (Input.touchCount > 1)
        {
            Touch touchA = Input.GetTouch(0);
            Touch touchB = Input.GetTouch(1);

            prePosA = touchA.position - touchA.deltaPosition;
            prePosB = touchB.position - touchB.deltaPosition;

            prePosMag = (prePosA - prePosB).magnitude;
            nowPosMag = (touchA.position - touchB.position).magnitude;

            touchPosMag = prePosMag - nowPosMag;

            Camera.main.orthographicSize += touchPosMag * zoomSpeed;
            Camera.main.orthographicSize = Mathf.Clamp(Camera.main.orthographicSize, 10.0f, 25.0f);
        }

        // 카메라 이동
        else if (Input.touchCount > 0)
        {
            Touch touch = Input.GetTouch(0);
            if (touch.phase == TouchPhase.Began)
            {
                prePos = touch.position;
            }
            if (touch.phase == TouchPhase.Moved)
            {
                nowPos = touch.position;

                movePos = new Vector3((prePos.x - nowPos.x) * 0.01f,
                                      (prePos.y - nowPos.y) * 0.01f,
                                       0);

                Camera.main.transform.Translate(movePos);
                prePos = touch.position - touch.deltaPosition;
            }
        }
        else
        {
            return;
        }
    }

    void CameraBorder()
    {
        // 카메라 위치를 특정 값에서 못 벗어나게 막는다
        Vector3 camBorder;
        Vector3 camPos = Camera.main.transform.position;
        camBorder.x = Mathf.Clamp(camPos.x, -30f, 30f);
        camBorder.y = Mathf.Clamp(camPos.y,   0f, 60f);
        camBorder.z = Mathf.Clamp(camPos.z, -30f, 30f);

        Camera.main.transform.position = camBorder;
    }

    public void ResetCam()
    {
        Camera.main.transform.position = new Vector3(0.0f, 30.0f, 0.0f);
    }
}