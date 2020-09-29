using UnityEngine;
using System.Collections;
using System;

public class GlobalLives : MonoBehaviour
{

    public GameObject LiveDisplay;
    public static int LiveCount = 3;
    public int InternalLive;

    void Update()
    {
        InternalLive = LiveCount;
        LiveDisplay.GetComponent<UnityEngine.UI.Text>().text = "" + LiveCount;
        if (LiveCount == 0)
        {
            Application.LoadLevel(3);
        }
    }
}