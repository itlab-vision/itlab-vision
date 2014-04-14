==========================
antique
==========================
Applies antique effect to the initial image.

.. cpp:function:: int antique(cv::InputArray src, cv::InputArray texture, cv::OutputArray dst)

    :param src: RGB image.
    :param texture: RGB image witch will be applied to **src** as texture of old photo.
    :param dst:Destination image of the same size and the same type as **src**.
    :return: Error code.

The algorithm.

#. Make texture the same size as the source image.
#. Apply sepia matrix transform to the **src**.
#. Calculate the weighted sum of the **texture** and **src**.
#. Save this matrix as image in same format as source image.

Example:

|srcImage| |dstImage|

.. |srcImage| image:: antiqueImage.jpeg
     :width: 20%

.. |dstImage| image:: antiqueOut.jpg
     :width: 20%