
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

#include "ofxUICustomImageButton.h"
#include "ofxUI.h"

ofxUICustomImageButton::ofxUICustomImageButton(float w, float h, bool _value, string _pathURL, string _name, int _size, int _labelWidth, int _labelHeight) : ofxUIButton()
{
    useReference = false;
    rect = new ofxUIRectangle(0,0,w,h);
    autoSize = true;
    init(&_value, _pathURL, _name, _size, _labelWidth, _labelHeight);
}

ofxUICustomImageButton::ofxUICustomImageButton(float w, float h, bool _value, string _pathURL, string _name, int _size, bool centerLabel) : ofxUIButton()
{
    useReference = false;
    rect = new ofxUIRectangle(0,0,w,h);
    int _labelWidth = w;
    int _labelHeight = 0;
    autoSize = centerLabel;
    init(&_value, _pathURL, _name, _size, _labelWidth, _labelHeight);
}

ofxUICustomImageButton::ofxUICustomImageButton(float w, float h, bool _value, ofImage *_img, string _name, int _size, int _labelWidth, int _labelHeight) : ofxUIButton()
{
    useReference = false;
    rect = new ofxUIRectangle(0,0,w,h);
    autoSize = true;
    init(&_value, _img, _name, _size, _labelWidth, _labelHeight);
}

ofxUICustomImageButton::ofxUICustomImageButton(float w, float h, bool _value, ofImage *_img, string _name, int _size, bool centerLabel) : ofxUIButton()
{
    useReference = false;
    rect = new ofxUIRectangle(0,0,w,h);
    int _labelWidth = w;
    int _labelHeight = 0;
    autoSize = centerLabel;
    init(&_value, _img, _name, _size, _labelWidth, _labelHeight);
}


ofxUICustomImageButton::~ofxUICustomImageButton()
{
    delete labelBackgroundRect;
    delete image;
}

void ofxUICustomImageButton::init(bool *_value, string _pathURL, string _name, int _size, int _labelWidth, int _labelHeight)
{
    name = string(_name);
    draw_outline = false;
    draw_outline_highlight = false;
    
    label = new ofxUILabel(0,0,(name+" LABEL"), name, _size);
    label->setParent(label);
    label->setRectParent(rect);
    label->setEmbedded(true);
    kind = OFX_UI_WIDGET_CUSTOMIMAGEBUTTON;
    
    paddedRect = new ofxUIRectangle(-padding, -padding, padding*2.0, padding*2.0);
    paddedRect->setParent(rect);
    
    labelBackgroundRect = new ofxUIRectangle(0,0,_labelWidth,_labelHeight);
    labelBackgroundRect->setParent(rect);
    
    image = new ofImage();
    image->loadImage(_pathURL);
    float iw = image->getWidth();
    float ih = image->getHeight();
    float aspect = ih/iw;
    
    if(iw > rect->getWidth())
    {
        image->resize(rect->getWidth(), rect->getWidth()*aspect);
    }
    
    rect->setWidth(image->getWidth());
    rect->setHeight(image->getHeight());
    
    if(useReference)
    {
        value = _value;
    }
    else
    {
        value = new bool();
        *value = *_value;
    }
    
    setValue(_value);
}

void ofxUICustomImageButton::init(bool *_value, ofImage *_img, string _name, int _size, int _labelWidth, int _labelHeight)
{
    name = string(_name);
    draw_outline = false;
    draw_outline_highlight = false;
    
    label = new ofxUILabel(0,0,(name+" LABEL"), name, _size);
    label->setParent(label);
    label->setRectParent(rect);
    label->setEmbedded(true);
    kind = OFX_UI_WIDGET_CUSTOMIMAGEBUTTON;
    
    paddedRect = new ofxUIRectangle(-padding, -padding, padding*2.0, padding*2.0);
    paddedRect->setParent(rect);
    
    labelBackgroundRect = new ofxUIRectangle(0,0,_labelWidth,_labelHeight);
    labelBackgroundRect->setParent(rect);
    
    image = _img;
    
    if(useReference)
    {
        value = _value;
    }
    else
    {
        value = new bool();
        *value = *_value;
    }
    
    setValue(_value);
}

void ofxUICustomImageButton::setParent(ofxUIWidget *_parent)
{
    parent = _parent;
    if(labelBackgroundRect->height == 0)
    {
        labelBackgroundRect->height = label->getPaddingRect()->height+padding*2.0;
    }
    ofxUIRectangle *labelrect = label->getRect();
    if(labelBackgroundRect->width == 0)
    {
        labelBackgroundRect->width = label->getPaddingRect()->width+padding*2.0;
    }
    else
    {
        while(labelrect->width > labelBackgroundRect->width)
        {
            string labelstring = label->getLabel();
            string::iterator it;
            it=labelstring.end();
            it--;
            labelstring.erase (it);
            label->setLabel(labelstring);
        }
    }
    
    float h = labelrect->getHeight();
    float ph = labelBackgroundRect->getHeight();
    
    float w = labelrect->getWidth();
    float pw = labelBackgroundRect->getWidth();
    
    
    labelrect->y = (int)(ph*.5 - h*.5);
    if(autoSize)
    {
        labelrect->x = (int)(pw*.5 - w*.5-padding*.5);
    }
    else
    {
        labelrect->x = padding*2.0;
    }
    paddedRect->height = rect->height+padding*2.0;
    paddedRect->width = rect->width+padding*2.0;
}

void ofxUICustomImageButton::drawBack()
{
    if(draw_back)
    {
        ofxUISetColor(255);
        image->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
        ofxUIFill();
        ofxUISetColor(color_back);
        labelBackgroundRect->draw();
    }
}

void ofxUICustomImageButton::drawOutline()
{

}

void ofxUICustomImageButton::drawOutlineHighlight()
{

}

void ofxUICustomImageButton::drawFill()
{
    if(draw_fill)
    {
        ofxUIFill();
        ofxUISetColor(color_fill);
        labelBackgroundRect->draw();
    }
}

void ofxUICustomImageButton::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ofxUIFill();
        ofxUISetColor(color_fill_highlight);
        labelBackgroundRect->draw();
    }
}

void ofxUICustomImageButton::setImage(ofImage *_image)
{
    if(image != NULL)
    {
        image->clear();
        delete image;
    }
    image = _image;
}