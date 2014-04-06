=========================================
Vignette
=========================================

<<<<<<< HEAD
Makes the edges of the photo less bright, creating an oval frame around its central part.

.. cpp:function:: int vignette(cv::InputArray src, cv::OutputArray dst, cv::Size rect)

   :param src: Source 8-bit three-channel image.
   :param dst: Destination image of the same size and the same type as **src**.
   :param rect: Size of rectangle describes an ellipse, whose center is at the center image.
   :return: Error code.

The algorithm.

#. Create a new 3-channel image, which is interpreted as BGR image.

#. For every channel calculate :math:`dist`, :math:`radius\_ellipse` and :math:`coefficient`, where
   :math:`dist` is a distance between the current pixel and the center of image;
   :math:`radius\_ellipse` is a radius of ellipse in the this point which belongs the same line as a pixel;
   :math:`coefficient` is a number which multiplies the intensity channel.

   The :math:`coefficient` is calculated by the following formula:

   .. math::

      coefficient = 1 - ((dist - radius\_ellipse) / (max\_radius - radius\_ellipse)),
   
   where :math:`max\_radius` is a distance between the pixel (0, img_src.cols) and the center image.

#. Convert image to a BGR format.

Example.

|srcImage| |dstImage|

.. |srcImage| image:: vignette_before.jpg
   :width: 40%

.. |dstImage| image:: vignette_after.jpg
   :width: 40%
=======
Makes the edges black white photos, creating an oval frame around its central part.

.. cpp:function:: int vignette(cv::InputArray src,
cv::OutputArray dst, cv::Size rect)

	:param src: Source 8-bit three-channel image.
	:param dst: Destination image of the same size and the same type as **src**.
	:param rect: Size of rectangle describes an ellipse, whose center is at the center image.
	:return: Error code.

The algorithm:

#. Creating new 3-channel image, which interpretted as BGR image.

	#. For every channel calculate dist, radius_ellipse and coefficient, where
		**dist** is a distance bitween the current pixel and the center image.
		**radius_ellipse** is a radius of ellipse in the this point which belongs the same line as a pixel.
		**coefficient** is a number which multiplies the intensity channel.

		The **coefficient** can be calculated by the following formula:
			**coefficient = 1 - ((dist - radius_ellipse) / (max_radius - radius_ellipse))**,
			where max_radius is a distance between the pixel (0, img_src.cols) and the center image.

#. Save this matrix as BGR image.
>>>>>>> Added warmify implementation and 2 files of rst-documentation
