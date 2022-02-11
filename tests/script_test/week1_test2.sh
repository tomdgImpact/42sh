#!/bin/sh

if true; true; false; then
    if false; then
        echo "ast is recursive"
    else
        echo "ast"
    fi
else
    echo "false"
fi
