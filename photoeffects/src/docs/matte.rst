=======================================
matte
=======================================
Applies matte effect to the initial image.

.. cpp:function:: int matte(cv::InputArray src, cv::OutputArray dst, cv::Point firstPoint, 
cv::Point secondPoint, float sigma)

    :param src: Source image.
    :param dst: Destination image of the same size and the same type as **src**.
    :param firstPoint: The first point for creating ellipse.
    :param secondPoint: The second point for creatin ellipse.
    :param sigma: The deviation in the Gaussian blur effect.
    :return: Error code.

The algorithm:

#. Create new image with white background for mask.
#. Build black ellipse by two points on the mask image - it's meaning part.
#. Use Gaussian Blur to meaning part for creating fade effect.
#. Accept mask to the image with convolution formula on all channels.
#. Save this matrix as image in same color format as **src**.

Example with sigma=25:

|srcImage| |dstImage|

.. |srcImage| image:: originalForMatte.jpg
    :width: 20%

.. |dstImage| image:: afterEffectMatte25.jpg
    :width: 20%