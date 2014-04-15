=======================================
Film Grain
=======================================
Applies film grain effect to the initial image.

.. cpp:function:: int filmGrain(InputArray src, OutputArray dst, int grainValue)

   :param src: Grayscale or RGB image.
   :param dst: Destination image of the same size and the same type as **src**.
   :param grainValue: Degree of graininess. 8 is default value. 
   
   :return: Error code.

The algorithm.

1. Convert image to **YUV** format. 
2. Add noise to first component. 
3. Convert image to **RGB** format.


Example.

|srcImage| |dstImage|

.. |srcImage| image:: film_grain_before.png
   :width: 40%

.. |dstImage| image:: film_grain_after.png
   :width: 40%
