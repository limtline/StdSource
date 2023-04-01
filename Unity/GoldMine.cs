using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

/// <summary>
/// 금광의 기능을 갖고 있다. 
/// 타운홀 1렙 기준 분당 60씩의 골드 생성,
/// 상점 안에서 버튼을 눌렀을때 동작하는 애니메이션.
public class GoldMine : MonoBehaviour
{
    GameObject btnI;
    Animator anim;

    public int myGold = 0;
    public int gold = 60;
    public float maxTime = 60f;

    public GoldStorage[] goldStorages = new GoldStorage[2];
    int index = 0;

    private void Awake()
    {
        btnI = transform.GetChild(1).gameObject;

        anim = GetComponent<Animator>();
    }
    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine(CountTime());
    }

    // Update is called once per frame
    void Update()
    {
        MouseClick();

        //Debug.Log(index);

        goldStorages = GameObject.FindObjectsOfType<GoldStorage>();
        if (index == goldStorages.Length - 1)
        {
            index = 0;
        }
        else
        {
            if (goldStorages[index].myGold == goldStorages[index].maxGold)
            {
                index++;
            }
            if(goldStorages[index].enabled==false)
            {
                index = 0;
            }
        }
        //Debug.Log("체크" + index);
    }

    public void BtnClick()
    {
        anim.SetTrigger("BtnClick");
    }

    public void MouseClick()
    {
        if (Input.GetMouseButtonDown(0))
        {
            Debug.Log("mouse");
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            if (Physics.Raycast(ray, out RaycastHit hit))
            {
                Debug.Log("rayhit");
                if (!EventSystem.current.IsPointerOverGameObject())
                {
                    Debug.Log("hook");
                    if (hit.collider.gameObject.name == "gold_mine_upg_01" || hit.collider.gameObject.name == "gold_mine_upg_01(Clone)")
                    {
                        if (myGold == 0)
                        {
                            Debug.Log("보유한 Gold가 없습니다.");
                            return;
                        }
                        if (myGold > gold)
                        {
                            Debug.Log($"Gold 회수: {this.myGold} Gold");
                            goldStorages[index].myGold += this.myGold;
                            this.myGold = 0;
                        }
                    }
                }
            }
        }
    }

    IEnumerator CountTime()
    {
        yield return new WaitForSeconds(maxTime);
        myGold += gold;
        //Debug.Log($"My Gold: {myGold}");

        StartCoroutine(CountTime());
    }

    void OnCollisionEnter(Collision col)
    {
        if(col.gameObject.tag == "Arrow")
            Destroy(gameObject);
    }
}
