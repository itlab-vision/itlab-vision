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

#. Define distance between center and corner of the image. This value will be maximal size of kernel.
	- For bluring we use gaussian filter with changing kernel.
	- All distance are calculated by this formula:
		**x^2 / a^2 + y^2 / b^2**,
		where **a = width / 2 - indentLeft, b = width / 2 - indentTop**,
		it is used for creating an ellipse around center.

#. For each pixel in src: if distance between center and this pixel more than 1, apply filter with kernels size equal that distance.

#. Save this matrix as RGB image.

Example:

|src| |dst|

.. |src| image:: 
    :width: 40%

.. |dst| image::
    :width: 40%