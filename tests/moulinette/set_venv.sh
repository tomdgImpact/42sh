#!/bin/sh

# before exec this script, check that you have python-venv package installed on
# your maachine

python -m venv mouli/
source mouli/bin/activate
pip install -r requirements.txt
