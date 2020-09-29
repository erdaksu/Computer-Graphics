using UnityEngine;
using System.Collections;

public class EnemyDeathScript : MonoBehaviour
{
    [System.Obsolete]
    IEnumerator OnTriggerEnter(Collider col)
    {
        _ = GlobalLives.LiveCount -= 1;
        yield return new WaitForSeconds(0.1f);
        Application.LoadLevel(2);
    }
}