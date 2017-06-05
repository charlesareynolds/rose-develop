#!/bin/bash

module load py-alabaster-0.7.10-gcc-4.7.1-hswcsfc
module load py-appdirs-1.4.3-gcc-4.7.1-rmr2su6
module load py-babel-2.4.0-gcc-4.7.1-p5vwpiu
module load py-docutils-0.13.1-gcc-4.7.1-4nylojk
 module load py-imagesize-0.7.1-gcc-4.7.1-5mv6cak
module load py-jinja2-2.9.6-gcc-4.7.1-mnz2iqh
module load py-markupsafe-1.0-gcc-4.7.1-pos6qio
module load py-packaging-16.8-gcc-4.7.1-euitqm7
#module load py-pip-9.0.1-gcc-4.7.1-ybco3hw
 module load py-pygments-2.2.0-gcc-4.7.1-mhkfbcr
module load py-pyparsing-2.2.0-gcc-4.7.1-swmmdjz
module load py-pytz-2017.2-gcc-4.7.1-5t2zwnn
 module load py-requests-2.14.2-gcc-4.7.1-d3g7mfv
#pkg_resources:
module load py-setuptools-35.0.2-gcc-4.7.1-yklkfqr
module load py-six-1.10.0-gcc-4.7.1-7bbqwwa
#module load py-snowballstemmer-1.2.1-gcc-4.7.1-kizpu6b
module load py-sphinx-1.6.1-gcc-4.7.1-qu2rxd4
module load py-sphinx-rtd-theme-0.2.5b1-gcc-4.7.1-di5iazc
module load py-sphinxcontrib-websupport-1.0.1-gcc-4.7.1-5pq4k5m
module load py-typing-3.6.1-gcc-4.7.1-uulsoye

#make html
python -msphinx -M html "." "_build"  
