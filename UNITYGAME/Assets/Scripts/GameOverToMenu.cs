using UnityEngine;
using System.Collections;


public class GameOverToMenu : MonoBehaviour
{

    IEnumerator Start()
    {
        GlobalLives.LiveCount += 3;
        yield return new WaitForSeconds(1f);
        Application.LoadLevel(0);
    }

}