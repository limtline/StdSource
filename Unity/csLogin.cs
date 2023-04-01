using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;
using UnityEngine.SceneManagement;
using UnityEngine.Networking;
using SimpleJSON;

public class csLogin : MonoBehaviour
{
    csPlayerInfo playerInfo;

    public InputField inputId;
    public InputField inputPass;
    public Text       txtLog;

    private string id;
    private string pass;
    private string pName;

    string phpURL = "http://unitycoc.dothome.co.kr/login.php";
    string jsonURL = "http://unitycoc.dothome.co.kr/login.json";

    void Awake()
    {
        playerInfo = GameObject.Find("PlayerInfo").GetComponent<csPlayerInfo>();
    }

    void Update()
    {
        id    = inputId.text;
        pass  = inputPass.text;
    }

    public void StartCoroutineLoginMember()
    {
        if (inputId.text == "" || inputPass.text == "")
        {
            txtLog.text = "공백 오류!!\n";
        }
        else
        {
            // 여기서 id나 pass 예외체크
            StartCoroutine("LoginMember");
        }
    }

    public IEnumerator LoginMember()
    {
        WWWForm form = new WWWForm();
        form.AddField("id", id);
        form.AddField("pass", pass);

        using (var www = UnityWebRequest.Post(phpURL, form))
        {
            yield return www.SendWebRequest();

            if (www.isNetworkError || www.isHttpError)
            {
                Debug.Log(www.error);
            }
            else
            {
                Debug.Log("upload complete");
                StartCoroutine("DisplayResult");
            }
        }
    }

    public IEnumerator DisplayResult()
    {
        using (var www = UnityWebRequest.Get(jsonURL))
        {
            yield return www.SendWebRequest();
            if (www.isNetworkError || www.isHttpError)
            {
                Debug.Log(www.error);
            }
            else
            {
                var strJsonData = www.downloadHandler.text;
                strJsonData = string.Join("", strJsonData.Split('[',']'));
                var jSon = JSON.Parse(strJsonData);

                var result = jSon["result"].ToString();

                if (result.CompareTo("\"IDFAIL\"") == 0)
                {
                    Debug.Log(result);
                    txtLog.text += "아이디 오류!!\n";
                }
                else if (result.CompareTo("\"PASSFAIL\"") == 0)
                {
                    Debug.Log(result);
                    txtLog.text += "비밀번호 오류!!\n";
                }
                else
                {
                    Debug.Log("SUCCESS");
                    txtLog.text += "로그인 성공!!\n";

                    playerInfo.id = id;
                    playerInfo.pName = jSon["name"];

                    SceneManager.LoadScene("scLoading");
                }
            }
        }
    }

    public void Join()
    {
        SceneManager.LoadScene("scJoin");
    }
}
