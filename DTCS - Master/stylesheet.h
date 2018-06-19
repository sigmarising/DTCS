#ifndef STYLESHEET_H
#define STYLESHEET_H


#define BUTTON_STYLESHEET(class_name,normal_color,normal_text_color,hover_color,hover_text_color,pressed_color,pressed_text_color)\
    (#class_name"{font: 18pt Bauhaus 93;border-style:none;padding:10px;border-radius:5px;color:"#normal_text_color";background:"#normal_color";}"\
    #class_name":hover{color:"#hover_text_color";background:"#hover_color";}"\
    #class_name":pressed{color:"#pressed_text_color";background:"#pressed_color";}")

#define TXT_STYLESHEET(class_name,normal_color,focus_color)\
    (#class_name"{font:15pt;border-style:none;padding:6px;border-radius:5px;border:2px solid "#normal_color";}"\
      #class_name":focus{border:2px solid "#focus_color";}")

#define TXTs_STYLESHEET(class_name,normal_color,focus_color)\
    (#class_name"{font:8pt;border-style:none;padding:6px;border-radius:5px;border:2px solid "#normal_color";}"\
      #class_name":focus{border:2px solid "#focus_color";}")

#define BAR_STYLESHEET(class_name,normal_color,chunk_color)\
    (#class_name"{font:10pt;height:8px;background:"#normal_color";border-radius:8px;text-align:center;border:1px solid "#normal_color";}"\
        #class_name":chunk{border-radius:8px;background-color:"#chunk_color";}")

#define  SLIDER_STYLESHEET(class_name,normal_color,groove_color,handle_color)\
    (#class_name"::groove:horizontal,QSlider::add-page:horizontal{height:8px;border-radius:4px;background:"#normal_color";}"\
        #class_name"::sub-page:horizontal{height:8px;border-radius:4px;background:"#groove_color";}"\
        #class_name"::handle:horizontal{width:13px;margin-top:-3px;margin-bottom:-3px;border-radius:6px;"\
                 "background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 #FFFFFF,stop:0.8 "#handle_color");}")


#endif // STYLESHEET_H
