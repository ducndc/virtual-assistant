/**
 * Author   : Chung Duc Nguyen Dang
 * Email    : nguyendangchungduc1999@gmail.com
 * 
 * eye_object.h
 */

#ifndef EYE_OBJECT_H
#define EYE_OBJECT_H

class EyeObject {
private:
	const char *m_pShades;
	
	int m_width; 
	int m_height;  
	
    float m_angle;
    float m_radius;

public:
	void Init(void);

	void DrawEye(float angleX, float angleY);

	void DisplayEye(void);

};

#endif /* END EYE_OBJECT_H */