using UnityEngine;
using System.Collections;

public class Life : MonoBehaviour
{
    public GameObject QuestionBlock;
    public GameObject DeadBlock;
    public GameObject LifeB;

    IEnumerator OnTriggerEnter(Collider col)
    {
        QuestionBlock.SetActive(false);
        DeadBlock.SetActive(true);
        yield return new WaitForSeconds(0.1f);
        LifeB.SetActive(true);
    }
}