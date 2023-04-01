using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;
using UnityEngine.SceneManagement;
using UnityEngine.Networking;
using SimpleJSON;

public class csJoin : MonoBehaviour
{
    public InputField inputId;
    public InputField inputPass;
    public InputField inputName;
    public Text       txtLog;

    private string id;
    private string pass;
    private string pName;

    string phpURL     = "http://unitycoc.dothome.co.kr/join.php";
    string infoPhpURL = "http://unitycoc.dothome.co.kr/memberInfo.php";
    string jsonURL    = "http://unitycoc.dothome.co.kr/join.json";

    void Update()
    {
        id    = inputId.text;
        pass  = inputPass.text;
        pName = inputName.text;
    }

    public void StartCoroutineSaveMember()
    {
        if (inputId.text == "" || inputPass.text == "" || inputName.text == "")
        {
            txtLog.text = "공백 체크!!\n";
        }
        else
        {
            // 여기서 id나 pass 예외체크
            StartCoroutine("SaveMember");
        }
    }

    public IEnumerator SaveMember()
    {
        WWWForm form = new WWWForm();
        form.AddField("id", id);
        form.AddField("pass", pass);
        form.AddField("name", pName);

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
                StartCoroutine("GetResult");
            }
        }
    }

    public IEnumerator GetResult()
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

                if (result.CompareTo("\"FAIL\"") == 0)
                {
                    Debug.Log("FAIL");
                    txtLog.text += "아이디 중복 오류!!\n";
                }
                else if (result.CompareTo("\"SUCCESS\"") == 0)
                {
                    Debug.Log("SUCCESS");
                    txtLog.text += "가입 성공!!\n";

                    StartCoroutine("SaveMemberInfo");
                }
            }
        }
    }

    IEnumerator SaveMemberInfo()
    {
        WWWForm form = new WWWForm();
        form.AddField("id", id);

        using (var www = UnityWebRequest.Post(infoPhpURL, form))
        {
            yield return www.SendWebRequest();

            if (www.isNetworkError || www.isHttpError)
            {
                Debug.Log(www.error);
            }
            else
            {
                Debug.Log("new memberInfo upload complete");
                SceneManager.LoadScene("scLogin");
            }
        }
    }

    public void Back()
    {
        SceneManager.LoadScene("scLogin");
    }
}
