using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletCtrl : MonoBehaviour
{
    public float speed;
    public bool homing;
    float timer;
    Vector3 disVec;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        // 1 GetComponent<Rigidbody>().AddForce(Vector3.forward * speed); // 월드좌표 z축 방향으로 진행.
        // 2 GetComponent<Rigidbody>().AddForce(transform.forward * speed); // 로컬좌표 z축 방향으로 진행.
        // 3 GetComponent<Rigidbody>().AddRelativeForce(transform.forward * speed); // 이상하게 움직임
        // 4 GetComponent<Rigidbody>().AddRelativeForce(Vector3.forward * speed);// 로컬좌표 z축 방향으로 진행.

        // 리지드바디의 AddForce 해도 되지만 이렇게 Translate 함수로 이동 시켜줘도 된다
        GetComponent<Rigidbody>().AddForce(transform.forward * speed);
        // // 거리 기록
        // dist += Time.deltaTime * speed;

        // // 만약 내가 설정한 위치에 도달하면 Destroy
        // if(dist >= range)
        // {
        //     //Instantiate(ExploPtcl, transform.position, transform.rotation);
        //     Destroy(gameObject);
        // }

        // 유닛이 존재하지 않을 시 총알 삭제
        if (!GameObject.FindGameObjectWithTag("ATTACKUNIT"))
        {
            Destroy(gameObject);
        }

        Destroy(gameObject, 2f); // 일정 시간뒤 총알 삭제

        // 대포알 유도기능
        // if (homing)
        // {
        //     if (GameObject.FindGameObjectWithTag("ATTACKUNIT"))
        //         disVec = (GameObject.FindGameObjectWithTag("ATTACKUNIT").GetComponent<Transform>().position - transform.position).normalized;

        //     if (!GameObject.FindGameObjectWithTag("ATTACKUNIT"))
        //     {
        //         Destroy(gameObject);
        //     }

        //     //transform.position += disVec * Time.deltaTime * speed;
        //     transform.forward = disVec;
        // }
    }

    // 충돌시 삭제
    void OnTriggerEnter(Collider col)
    {
        //Instantiate(ExploPtcl, transform.position, transform.rotation);

        if (col.tag == "ATTACKUNIT")
        {
            Destroy(gameObject);
        }
    }


}
