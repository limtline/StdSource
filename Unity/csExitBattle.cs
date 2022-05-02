using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.SceneManagement;

public class csExitBattle : MonoBehaviour
{
    public void ExitBattle()
    {
        Destroy(GameObject.FindObjectOfType<BattleManager>().gameObject);
        GameObject.FindObjectOfType<csPlayerInfo>().townLoaded = false;
        SceneManager.LoadScene("scPlay");
    }
}
