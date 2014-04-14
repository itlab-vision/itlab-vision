=======================================
Edge Blur
=======================================
Blurs the edges of the initial image, keeping center in focus.

.. cpp:function:: int edgeBlur(InputArray src, OutputArray dst, int indentTop, int indentLeft)

    :param src: RGB image.
    :param dst: Destination image of the same size and the same type as **src**.
    :param indentTop: The indent from the top and the bottom of the image. It will be blured.
    :param indentLeft: The indent from the left and right side of the image. It will be blured.
    :return: Error code.

The algorithm:

#. Define distance between center and corner of the image. This value will be maximal size of the kernel.
	- For bluring we use gaussian filter with changing kernel.
	- All distance are calculated by this formula:
            | **x^2 / a^2 + y^2 / b^2**,
            | where **a = width / 2 - indentLeft, b = height / 2 - indentTop**,
            | it is used for creating an ellipse around center.

#. Create image with border - **bearingImage** from **src** (border size = maximal size of kernel), pixels on border is a copy pixels from the edges. 

#. For each pixel of **bearingImage** (except border): if distance between center and this pixel more than 1, apply filter with kernel size equal that distance, then write value to output image (**dst**).

#. Other pixels we copy to **dst**.

Example:
    **indentTop** = 90, **indentLeft** = 90.

|src| |dst|

.. |src| image:: originalForEdgeBlur.png
    :width: 40%

.. |dst| image:: edgeBlur.png
    :width: 40%