using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BallController : MonoBehaviour
{
    public MeshCollider mazeCollider;
    public Transform ballPosition;

    void Update()
    {

        mazeCollider.enabled = false;

        if (Input.GetKeyDown(KeyCode.R))
        {
            ballPosition.localPosition = Vector3.zero;
        }

        mazeCollider.enabled = true;

    }
}
