using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using UnityEngine.SceneManagement;

using CoCInterface;

[System.Serializable]
// 애니메이션 클립을 저장할 클래스
public class Anim
{
    public AnimationClip idle;
    public AnimationClip move;
    public AnimationClip attack;
    public AnimationClip die;
}

public class Archer : MonoBehaviour
{
    [Header("AMIMATION")]
    [Space(30)]
    public Anim anims;
    private Animation _anim;

    public tUnitInfo archer;
    [HideInInspector]
    public bool isDie = true;

    public Transform arrow;
    public Transform firepos;
    private bool buildCheck;

    private NavMeshAgent myTraceAgent;
    private Transform traceTarget;

    private GameObject[] build;
    private Transform buildTarget;

    private Transform myTr;
    float dist;
    float dist1;
    float dist2;

    float arrowSpeed;

    [HideInInspector]
    public bool shot;

    public AudioClip attackSound;
    AudioSource audioSource;

    private bool isHit;
    public enum MODE_STATE { IDLE = 1, MOVE, TRACE, ATTACK, HIT, DIE };

    public MODE_STATE enemyMode = MODE_STATE.IDLE;

    void Awake()
    {
        archer = new tUnitInfo();
        myTraceAgent = GetComponent<NavMeshAgent>();
        myTr = GetComponent<Transform>();
        _anim = GetComponentInChildren<Animation>();
        audioSource = GetComponent<AudioSource>();
        build = GameObject.FindGameObjectsWithTag("BUILDING");

        AInfo();
    }

    // Start is called before the first frame update
    IEnumerator Start()
    {
        traceTarget = build[0].transform;
        _anim.clip = anims.idle;
        _anim.Play();


        // _anim.clip = _anims.move;
        // _anim.Play();
        yield return null;
    }

    void OnEnable()
    {
        // 정해진 시간 간격으로 Enemy의 Ai 변화 상태를 셋팅하는 코루틴
        StartCoroutine(ModeSet());
        // Enemy의 상태 변화에 따라 일정 행동을 수행하는 코루틴
        StartCoroutine(ModeAction());

        //StartCoroutine(ShotSetting());
    }

    // Update is called once per frame
    void Update()
    {
        // scAttack 신에서만 적용되게한다
        if (SceneManager.GetActiveScene().name == "scAttack")
        {
            if (traceTarget != null)
            {
                // 건물들을 타겟으로 잡는다.
                myTraceAgent.SetDestination(traceTarget.position);
            }
            // 총알 발사
            if (shot)
            {
                if (Time.time > arrowSpeed)
                {
                    // bool 형을 이용하여 코루틴이 시작하자마자 타는것을 방지
                    AShot();
                    arrowSpeed = Time.time + 2f;
                }

            }

            // 총알이 발사되지 않을 때
            if (!shot)
            {
                // 건물들이 죽으면 다른 건물을 찾는다.
                Target();
            }

            // 체력이 0 이되면 죽는다.
            if (archer.uHp <= 0)
            {
                DieStart();
            }

            if (buildTarget == null)
            {
                buildCheck = false;
                shot = false;
            }

            if (!GameObject.FindGameObjectWithTag("BUILDING"))
            {
                Destroy(audioSource);
            }
        }
    }

    // 궁수의 정보들
    void AInfo()
    {
        archer.uInfo = "궁수 입니다.";
        archer.uName = "궁수";
        archer.uHp = 10;
        archer.uDamage = 40;
        archer.uLevel = 1;
        archer.uDevelopmentTime = 3.0f;
        archer.uAttackSpeed = 40.0f;    // ?
        archer.uMoveSpeed = 10.0f;      // ?
        archer.uPopulation = 1;
        archer.uPrice = 30;
    }

    public void Target()
    {
        StartCoroutine(this.TargetSetting());
        StartCoroutine(this.ShotSetting());
    }

    // 건물들을 찾는다
    IEnumerator TargetSetting()
    {
        while (!buildCheck)
        {
            yield return new WaitForSeconds(0.2f);

            // 자신과 가장 가까운 건물 찾음
            build = GameObject.FindGameObjectsWithTag("BUILDING");
            //건물이 있을경우 
            if (build.Length != 0)
            {
                buildTarget = build[0].transform;
                dist1 = (buildTarget.position - myTr.position).sqrMagnitude;
            }

            foreach (GameObject _builds in build)
            {
                if ((_builds.transform.position - myTr.position).sqrMagnitude < dist1)
                {
                    buildTarget = _builds.transform;
                    dist1 = (buildTarget.position - myTr.position).sqrMagnitude;
                }

            }
        }
    }

    private void AShot()
    {
        if (shot)
            StartCoroutine(this.ShotStart());
    }

    // 화살 발사 코루틴
    IEnumerator ShotStart()
    {
        yield return new WaitForSeconds(0.5f);

        Arrow ar = Instantiate(arrow, firepos.position, firepos.rotation).GetComponent<Arrow>();
        //ar.homing = true;
        buildCheck = true;
    }

    // 가장 가까운 적을 찾아 발사...
    IEnumerator ShotSetting()
    {
        while (!buildCheck)
        {
            yield return new WaitForSeconds(0.2f);

            if (buildTarget != null)
            {
                dist2 = Vector3.Distance(myTr.position, buildTarget.position);
            }

            if (dist2 <= 15.0f)
            {
                shot = true;
            }
        }
    }

    // 공격 받을 시 데미지 받는 부분
    void OnTriggerEnter(Collider col)
    {
        if (col.tag == "Bullet")
        {
            archer.uHp -= 3;
        }
    }

    IEnumerator ModeSet()
    {
        while (!isDie)
        {
            yield return new WaitForSeconds(0.2f);


            // 자신과 건물 거리 셋팅
            if (buildTarget != null)
            {
                dist = Vector3.Distance(myTr.position, buildTarget.position);
            }

            // 순서 중요
            if (isHit)   //공격 받았을시
            {
                enemyMode = MODE_STATE.HIT;
            }

            else if (dist < 15.0f)  // Attack 사거리에 들어왔는지 ?? 15.0f
            {
                enemyMode = MODE_STATE.ATTACK;      // 유닛의 상태를 공격으로 설정
                yield return new WaitForSeconds(1f);
                audioSource.PlayOneShot(attackSound, attackSound.length);
            }

            else if (buildTarget != null) //  배고플 때 (주인공 찾는다)
            {
                enemyMode = MODE_STATE.MOVE;        // 유닛의 상태를 이동으로 설정
            }

            else if (buildTarget == null) //  타겟이 존재 하지 않을 시
            {
                enemyMode = MODE_STATE.IDLE;        // 유닛의 상태를 idle 모드로 설정 
            }

            else
            {
                enemyMode = MODE_STATE.MOVE;        // 유닛의 상태를 move 모드로 설정 
            }

        }
    }

    IEnumerator ModeAction()
    {
        while (!isDie)
        {
            switch (enemyMode)
            {
                //Enemy가 Idle 상태 일때...
                case MODE_STATE.IDLE:

                    //네비게이션 멈추고 (추적 중지)
                    myTraceAgent.isStopped = true;
                    shot = false;
                    //idle1 애니메이션 
                    _anim.CrossFade(anims.idle.name, 0.3f);

                    // 포톤 추가
                    // 애니메이션 동기화
                    // net_Anim = 0;

                    break;

                //Enemy가 Trace 상태 일때...
                // case MODE_STATE.TRACE:

                //     // 네비게이션 재시작(추적)
                //     myTraceAgent.isStopped = false;
                //     // 추적대상 설정(플레이어)
                //     myTraceAgent.destination = traceTarget.position;

                //     //네비속도 및 애니메이션 속도 제어
                //     if(enemyKind == MODE_KIND.ENEMYBOSS)
                //     {
                //         // 네비게이션의 추적 속도를 현재보다 1.8배
                //         myTraceAgent.speed = speed * 1.8f;

                //         //애니메이션 속도 변경
                //         _anim[anims.move.name].speed = 1.8f;

                //         //run 애니메이션 
                //         _anim.CrossFade(anims.move.name, 0.3f);

                //         // 포톤 추가
                //         // 애니메이션 동기화
                //         net_Anim = 4;
                //     }
                //     else
                //     {
                //         // 네비게이션의 추적 속도를 현재보다 1.5배
                //         myTraceAgent.speed = speed * 1.5f;

                //         //애니메이션 속도 변경
                //         _anim[anims.move.name].speed = 1.5f;

                //         //run 애니메이션 
                //         _anim.CrossFade(anims.move.name, 0.3f);

                //         // 포톤 추가
                //         // 애니메이션 동기화
                //         net_Anim = 5;
                //     }
                // break;

                //공격 상태
                case MODE_STATE.ATTACK:
                    //사운드 (공격)

                    //추적 중지(선택사항)
                    //네비게이션 멈추고 (추적 중지)
                    myTraceAgent.isStopped = true;

                    //공격할때 적을 봐라 봐야함 
                    // myTr.LookAt(traceTarget.position); // 바로 봐라봄
                    // enemyLookRotation.eulerAngles = new Vector3(myTr.rotation.x, enemyLookRotation.eulerAngles.y, myTr.rotation.z);
                    if (buildTarget != null)
                    {
                        Quaternion enemyLookRotation = Quaternion.LookRotation(buildTarget.position - myTr.position);
                        myTr.rotation = Quaternion.Lerp(myTr.rotation, enemyLookRotation, Time.deltaTime * 10.0f);
                        isDie = false;
                    }

                    //attack1 애니메이션
                    _anim.CrossFade(anims.attack.name, 0.3f);

                    // 포톤 추가
                    // 애니메이션 동기화
                    // net_Anim = 6;

                    break;

                //이동 상태 
                case MODE_STATE.MOVE:

                    // 네비게이션 재시작(추적)
                    myTraceAgent.isStopped = false;
                    shot = false;
                    // 추적대상 설정(로밍장소)
                    //myTraceAgent.destination = roamingTarget.position;

                    //네비속도 및 애니메이션 속도 제어
                    // if(enemyKind == MODE_KIND.ENEMYBOSS)
                    // {
                    //     // 네비게이션의 추적 속도를 현재보다 1.2배
                    //     myTraceAgent.speed = speed * 1.2f;

                    //     //애니메이션 속도 변경
                    //     _anim[anims.move.name].speed = 1.2f;

                    //     //run 애니메이션 
                    //     _anim.CrossFade(anims.move.name, 0.3f);

                    //     // 포톤 추가
                    //     // 애니메이션 동기화
                    //     net_Anim = 10;
                    // }

                    // 네비게이션의 추적 속도를 현재 속도로...
                    myTraceAgent.speed = 1.0f;
                    //애니메이션 속도 변경
                    _anim[anims.move.name].speed = 1.0f;

                    //walk 애니메이션 
                    _anim.CrossFade(anims.move.name, 0.3f);

                    // 포톤 추가
                    // 애니메이션 동기화
                    //net_Anim = 11;
                    break;
            }
            yield return null;
        }
    }

    public void DieStart()
    {
        StartCoroutine(this.Die());
    }

    // 죽는 코루틴
    IEnumerator Die()
    {
        isDie = true;
        _anim.CrossFade(anims.die.name, 0.3f);
        enemyMode = MODE_STATE.DIE;
        this.gameObject.tag = "Untagged";
        myTraceAgent.isStopped = true;

        foreach (Collider col in gameObject.GetComponentsInChildren<Collider>())
        {
            col.enabled = false;
        }

        yield return new WaitForSeconds(0.1f);
        Destroy(gameObject);
    }
}
