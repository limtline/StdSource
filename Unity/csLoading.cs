using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;
using UnityEngine.Networking;
using UnityEngine.SceneManagement;
using SimpleJSON;

public class csLoading : MonoBehaviour
{
    csPlayerInfo playerInfo;
    public Slider loadingBar;
    public Text loadingTxt;

    // Start is called before the first frame update
    void Start()
    {
        playerInfo = GameObject.FindWithTag("Player").GetComponent<csPlayerInfo>();

        StartCoroutine("LoadResources");
    }

    IEnumerator LoadResources()
    {
        loadingTxt.text = "재화 로딩중...";

        WWWForm form = new WWWForm();
        form.AddField("id", playerInfo.id);

        using (var www = UnityWebRequest.Post(playerInfo.resourceManager.phpURL, form))
        {
            yield return www.SendWebRequest();

            loadingBar.value += www.uploadProgress / 2.0f;

            if (www.isNetworkError || www.isHttpError)
            {
                Debug.Log(www.error);
            }
            else
            {
                StartCoroutine("GetResources");
            }
        }
    }

    IEnumerator GetResources()
    {
        using (var www = UnityWebRequest.Get(playerInfo.resourceManager.jsonURL))
        {
            yield return www.SendWebRequest();

            loadingBar.value += www.downloadProgress / 2.0f;

            if (www.isNetworkError || www.isHttpError)
            {
                Debug.Log(www.error);
            }
            else
            {
                var strJsonData = www.downloadHandler.text;
                strJsonData = string.Join("", strJsonData.Split('[',']'));
                var jSon = JSON.Parse(strJsonData);

                playerInfo.gold    = jSon["gold"].AsInt;
                playerInfo.mana    = jSon["mana"].AsInt;
                playerInfo.emerald = jSon["emerald"].AsInt;

                
                Debug.Log("Resources complete");

                loadingBar.value = 0.0f;
                StartCoroutine("LoadTown");
            }
        }
    }

    IEnumerator LoadTown()
    {
        loadingTxt.text = "마을 배치 로딩중...";
        
        WWWForm form = new WWWForm();
        form.AddField("id", playerInfo.id);

        using (var www = UnityWebRequest.Post(playerInfo.townManager.phpURL, form))
        {
            yield return www.SendWebRequest();

            loadingBar.value += www.uploadProgress / 2.0f;

            if (www.isNetworkError || www.isHttpError)
            {
                Debug.Log(www.error);
            }
            else
            {
                StartCoroutine("GetTown");
            }
        }
    }

    IEnumerator GetTown()
    {
        using (var www = UnityWebRequest.Get(playerInfo.townManager.jsonURL))
        {
            yield return www.SendWebRequest();

            loadingBar.value += www.downloadProgress / 2.0f;
            
            if (www.isNetworkError || www.isHttpError)
            {
                Debug.Log(www.error);
            }
            else
            {
                var strJsonData = www.downloadHandler.text;
                var jSon = JSON.Parse(strJsonData);

                for (int i = 0; i < jSon.Count; i++)
                {
                    BuildingI building = new BuildingI();
                    building.name = jSon[i]["name"].ToString();
                    building.name = string.Join("", building.name.Split('\"'));
                    building.x    = jSon[i]["x"].AsInt;
                    building.z    = jSon[i]["z"].AsInt;

                    playerInfo.townManager.buildings.Add(building);

                    Debug.Log("name : " + building.name + "  x : " + building.x + "  z : " + building.z);
                }
                
                Debug.Log("TownLoad complete");                
                StartCoroutine("LoadArmy");
            }
        }
    }

    IEnumerator LoadArmy()
    {
        loadingTxt.text = "나의 군대 로딩중...";
        
        WWWForm form = new WWWForm();
        form.AddField("id", playerInfo.id);

        using (var www = UnityWebRequest.Post(playerInfo.armyManager.phpURL, form))
        {
            yield return www.SendWebRequest();

            loadingBar.value += www.uploadProgress / 2.0f;

            if (www.isNetworkError || www.isHttpError)
            {
                Debug.Log(www.error);
            }
            else
            {
                StartCoroutine("GetArmy");
            }
        }
    }

    IEnumerator GetArmy()
    {
        using (var www = UnityWebRequest.Get(playerInfo.armyManager.jsonURL))
        {
            yield return www.SendWebRequest();

            loadingBar.value += www.downloadProgress / 2.0f;
            
            if (www.isNetworkError || www.isHttpError)
            {
                Debug.Log(www.error);
            }
            else
            {
                var strJsonData = www.downloadHandler.text;
                var jSon = JSON.Parse(strJsonData);

                for (int i = 0; i < jSon.Count; i++)
                {
                    UnitI unit = new UnitI();
                    unit.name  = jSon[i]["name"].ToString();
                    unit.name  = string.Join("", unit.name.Split('\"'));
                    unit.level = jSon[i]["level"].AsInt;
                    unit.num   = jSon[i]["num"].AsInt;

                    playerInfo.armyManager.units.Add(unit);
                }
                
                Debug.Log("ArmyLoad complete");

                StartCoroutine("GoPlay");
            }
        }
    }

    IEnumerator GoPlay()
    {
        yield return new WaitForSeconds(1);
        playerInfo.armyManager.enabled = true;
        SoundManager.Instance.PlayBGM();
        SceneManager.LoadScene("scPlay");
    }
}
