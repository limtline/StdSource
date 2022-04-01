using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using CoCInterface;
using UnityEngine.SceneManagement;

public class Cannon : MonoBehaviour
{
    public tBuildingInfo cannon;
    [HideInInspector]
    public bool isDie;

    public float dist2;

    public Transform bullet;
    public Transform firepos;

    private int damage = 1;
    private bool shot;
    private bool check;
    private bool enemyCheck;

    private float bulletSpeed;

    //Enemy를 찾기 위한 배열
    private GameObject[] enemy;
    private Transform EnemyTarget;

    private Transform myTr;
    private Quaternion enemyLookRotation;
    private float enemyLookTime;

    void Awake()
    {
        myTr = GetComponent<Transform>();
        cannon = new tBuildingInfo();
        CInfo();
    }

    // Start is called before the first frame update
    IEnumerator Start()
    {
        //StartCoroutine(this.ShotStart());
        yield return null;
    }

    // Update is called once per frame
    void Update()
    {
        // scAttack 신에서만 실행되게함
        if (SceneManager.GetActiveScene().name == "scAttack")
        {
            // 캐논 발사
            if (shot)
            {
                if (Time.time > bulletSpeed)
                {
                    CShot();
                    bulletSpeed = Time.time + 1.5f;
                }

            }

            // 캐논 발사 안할 시 타겟 추적
            if (!shot)
            {
                TargetSet();
            }

            // 캐논 의 피가 0 이되면 사라진다.
            if (cannon.bHp <= 0)
            {
                StartDie();
            }

            // 적이 존재하지 않으면 발시 하지도 않고 포신을 돌리지도 않는다.
            if (EnemyTarget == null)
            {
                BoolSet();
            }
        }
    }

    // 포신 회전
    void BarralRotation()
    {
        enemyLookRotation = Quaternion.LookRotation(EnemyTarget.position - myTr.position); // - 해줘야 바라봄  
        myTr.rotation = Quaternion.Lerp(myTr.rotation, enemyLookRotation, Time.deltaTime * 150f);
        //enemyLookTime = Time.time * 2f;
    }

    private void CShot()
    {
        StartCoroutine(this.ShotStart());
    }

    // 총알 발사 코루틴
    IEnumerator ShotStart()
    {
        BarralRotation();
        yield return new WaitForSeconds(0.5f);
        BulletCtrl bcl = Instantiate(bullet, firepos.position, firepos.rotation).GetComponent<BulletCtrl>();
        //bcl.homing = true; // 대포알 유도기능
        enemyCheck = true;
    }

    private void TargetSet()
    {
        StartCoroutine(this.TargetSetting());
        StartCoroutine(this.ShotSetting());
    }

    // 적 유닛 찾는 코루틴
    IEnumerator TargetSetting()
    {
        while (!enemyCheck)
        {
            yield return new WaitForSeconds(0.2f);

            // 자신과 가장 가까운 플레이어 찾음
            enemy = GameObject.FindGameObjectsWithTag("ATTACKUNIT");

            foreach (GameObject _Enemy in enemy)
            {
                Transform EnemyTargets = enemy[0].transform;

                float dist = (EnemyTargets.position - myTr.position).sqrMagnitude;


                if ((_Enemy.transform.position - myTr.position).sqrMagnitude < dist)
                {
                    EnemyTargets = _Enemy.transform;
                    dist = (EnemyTargets.position - myTr.position).sqrMagnitude;
                }

                EnemyTarget = EnemyTargets;
                //BarralRotation();
            }
        }
    }

    // 가장 가까운 적을 찾아 발사...
    IEnumerator ShotSetting()
    {
        while (!enemyCheck)
        {
            yield return new WaitForSeconds(0.2f);

            enemy = GameObject.FindGameObjectsWithTag("ATTACKUNIT");
            if (EnemyTarget != null)
            {
                dist2 = Vector3.Distance(myTr.position, EnemyTarget.position);

                if (dist2 < 25.0f)
                {
                    shot = true;
                }
                else
                {
                    shot = false;
                }
            }
        }
    }

    // 공격을 받을 시 데미지 받는 부분
    void OnTriggerEnter(Collider col)
    {
        if (col.tag == "Arrow")
        {
            cannon.bHp -= 100;
            Debug.Log(cannon.bHp);
        }
    }

    // 적이 죽거나 존재 하지않을때 공격을 멈추게 하는 bool형 설정
    void BoolSet()
    {
        isDie = true;
        shot = false;
        enemyCheck = false;
    }

    // 캐논의 정보
    void CInfo()
    {
        cannon.bInfo = "캐논";
        cannon.bName = "캐논";
        cannon.bHp = 300;
        cannon.bPrice = 500; // 골드
        cannon.bDevelopmentTime = 20f; // 건설 시간 <- 20초
        cannon.bLevel = 1;
    }

    public void StartDie()
    {
        StartCoroutine(this.Die());
    }

    // 죽는 코루틴
    IEnumerator Die()
    {
        isDie = true;
        this.gameObject.tag = "Untagged";

        foreach (Collider col in gameObject.GetComponentsInChildren<Collider>())
        {
            col.enabled = false;
        }

        yield return null;
        Destroy(transform.parent.gameObject);
    }
}