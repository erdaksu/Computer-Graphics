using UnityEngine;
using System.Collections;

public class DeathScript2 : MonoBehaviour
{
    public AudioSource Death;
    IEnumerator OnTriggerEnter(Collider col)
    {
        Death.Play();
        GlobalLives.LiveCount -=1;
        GlobalCoins.CoinCount = 0;
        yield return new WaitForSeconds(1f);
        Application.LoadLevel(7);
    }
}