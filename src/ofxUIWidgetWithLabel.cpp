/**********************************************************************************
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#include "ofxUIWidgetWithLabel.h"

ofxUIWidgetWithLabel::ofxUIWidgetWithLabel() : ofxUIWidget()
{
    
}

ofxUIWidgetWithLabel::~ofxUIWidgetWithLabel()
{
    
}

bool ofxUIWidgetWithLabel::ofxUIWidgetWithLabel::hasLabel()
{
    return true;
}

void ofxUIWidgetWithLabel::setVisible(bool _visible)
{
    visible = _visible;
    ofxUIWidget *labelWidget = (ofxUIWidget *) label;
    labelWidget->setVisible(visible);
}

ofxUILabel* ofxUIWidgetWithLabel::getLabelWidget()
{
    return label;
}

void ofxUIWidgetWithLabel::toggleColors()
{
    ofxUIColor fill = getColorFill();
    float af = fill.a;
    ofxUIColor back = getColorBack();
    float ab = back.a;
    
    setColorFill(ofxUIColor(back, af));
    setColorBack(ofxUIColor(fill, ab));
}

void ofxUIWidgetWithLabel::setModal(bool _modal)
{
    modal = _modal;
    ofxUIWidget *labelWidget = (ofxUIWidget *) label;
    labelWidget->setModal(modal);
    if(parent != NULL)
    {
        if(modal)
        {
            parent->addModalWidget(this);
        }
        else
        {
            parent->removeModalWidget(this);
        }
    }
}