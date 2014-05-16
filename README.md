# ITLab Vision Group

[![Build Status](https://travis-ci.org/UNN-VMK-Software/itlab-vision.png?branch=master)](https://travis-ci.org/UNN-VMK-Software/itlab-vision) [![Coverage Status](https://coveralls.io/repos/UNN-VMK-Software/itlab-vision/badge.png)](https://coveralls.io/r/UNN-VMK-Software/itlab-vision)

------------------

This project is developed at Nizhny Novgorod State University (ITLab laboratory)
and supported by the [Itseez](http://itseez.com) company.

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

## Build and Run instructions

Build:

```
    $ mkdir photofilters
    $ cd photofilters
    $ git clone https://github.com/UNN-VMK-Software/itlab-vision.git
    $ mkdir build
    $ cd build
    $ cmake ../itlab-vision/photoeffects/
    $ make
    $ cd ./bin
```

Tests execution:

```
    $ ./photoeffects_test
```

Samples execution (test images are used):

```
    $ ./antique_sample testdata/antique_test.png testdata/antique_texture_test.png 0.7
    $ ./edgeBlur_sample testdata/edgeBlur_test.png
    $ ./filmGrain_sample testdata/filmGrain_test.png 7
    $ ./matte_sample testdata/matte_test.png 25 25
    $ ./vignette_sample testdata/antique_test.png
    $ ./boostColor_sample  testdata/boostColor_test.png 0.2
    $ ./fadeColor_sample testdata/fadeColor_test.png
    $ ./glow_sample testdata/glow_test.png 25 0.8
    $ ./sepia_sample testdata/antique_test.png
    $ ./tint_sample testdata/antique_test.png
    $ ./warmify_sample testdata/antique_test.png
```
