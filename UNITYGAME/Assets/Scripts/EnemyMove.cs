using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyMove : MonoBehaviour
{
    public float LeftPoint = 16.95F;
    public float RightPoint = 19.95F;
    public int Direction = 1;
    //public Vector3 offset;

    void Update()
    {
        if (Direction == 1)
        {
            transform.Translate(Vector3.right * 2 * Time.deltaTime, Space.World);
            Direction = 1;
        }
        if (this.transform.position.x > RightPoint)
        {
            Direction = 2;
        }

        if (Direction == 2)
        {
            transform.Translate(Vector3.right * -2 * Time.deltaTime, Space.World);
            Direction = 2;
        }
        if (this.transform.position.x < LeftPoint)
        {
            Direction = 1;
        }
    }
}