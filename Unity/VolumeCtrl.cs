using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class VolumeCtrl : MonoBehaviour
{
    public Slider sliBGM;
    public Slider sliSFX;
    public Toggle togMUTE;
    
    public void SetBgmVolume()
    {
        SoundManager.Instance.BgmVolume = sliBGM.value;
        SoundManager.Instance.AudioSet();
    }

    public void SetSfxVolume()
    {
        SoundManager.Instance.SfxVolume = sliSFX.value;
        SoundManager.Instance.AudioSet();
    }

    public void SetMute()
    {
        SoundManager.Instance.IsMute = togMUTE.isOn;
        SoundManager.Instance.AudioSet();
    }
}
