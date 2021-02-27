#!/bin/sh
doxybook2 --input ../build/doxygen/xml --output ../misc/hugo-docs/content/docs/api --config ../misc/doxybook-hugo-config.json --templates ../misc/doxybook-templates

# doxybook2 --input ../build/doxygen/xml --output ../misc/hugo-docs/content/docs/api --config ../misc/doxybook-hugo-config.json
