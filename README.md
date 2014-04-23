# ITLab Vision Group

[![Build Status](https://travis-ci.org/UNN-VMK-Software/itlab-vision.png?branch=master)](https://travis-ci.org/UNN-VMK-Software/itlab-vision)

This project is developed at Nizhny Novgorod State University (ITLab laboratory) and supported by [Itseez](http://itseez.com) company.

Resources:

  - Documentation: http://itlab-vision.readthedocs.org

Project maintainers:

  - Valentina Kustikova
  - Pavel Druzhkov
  - Kirill Kornyakov

Project developers:
  - Evgeniy Dolotov
  - Artem Screbkov
  - Dmitriy Kruchinin
  - Vadim Levin
  - Vlad Vinogradov



Build instructions:

    >mkdir photofilters
    >cd photofilters/
    >git clone https://github.com/UNN-VMK-Software/itlab-vision.git
    >mkdir build
    >cd build/
    >cmake ../itlab-vision/photoeffects/
    >make
    >cd ./bin/

Tests execution:

    >./photoeffects_test

Samples execution (test images are used):
  1. Antique

    ```
    ./antique_sample testdata/antique_test.png testdata/antique_texture_test.png 0.7
    ```

  2. Edge Blur

    ```
    ./edgeBlur_sample testdata/edgeBlur_test.png
    ```

  3. Film Grain

    ```
    ./filmGrain_sample testdata/filmGrain_test.png 7
    ```

  4. Matte

    ```
    ./matte_sample testdata/matte_test.png 25 25
    ```

  5. Vignette

    ```
    ./vignette_sample testdata/antique_test.png
    ```

  6. Boost Color

    ```
    ./boostColor_sample  testdata/boostColor_test.png 0.2
    ```

  7. Fade Color

    ```
    ./fadeColor_sample testdata/fadeColor_test.png
    ```

  8. Glow

    ```
    ./glow_sample testdata/glow_test.png 25 0.8
    ```

  9. Sepia

    ```
    ./sepia_sample testdata/antique_test.png
    ```

  10. Tint

    ```
    ./tint_sample testdata/antique_test.png
    ```

  11. Warmify

    ```
    ./warmify_sample testdata/antique_test.png
    ```
