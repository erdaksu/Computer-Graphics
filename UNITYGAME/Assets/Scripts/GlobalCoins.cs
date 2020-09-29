using UnityEngine;
using System.Collections;
using System;

public class GlobalCoins : MonoBehaviour
{

    public GameObject CoinDisplay;
    public static int CoinCount;
    public int InternalCoin;

    void Update()
    {
        InternalCoin = CoinCount;
        CoinDisplay.GetComponent<UnityEngine.UI.Text>().text = "COINS: " + CoinCount;
    }
}