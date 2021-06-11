/*
 * GLObjManager.h
 *
 *  Created on: 2014-11-16
 *      Author: wei
 */

#ifndef GLOBJMANAGER_H_
#define GLOBJMANAGER_H_
#include <vector>
#include "GLObject.h"
namespace cjw3d {
   std::vector<GLObject> arr;
class GLObjManager {
private:
	GLObject **objs;
	int objNum;
public:
	GLObjManager();
	~GLObjManager();
	void addObj();
	void deleteObj();
};

} /* namespace cjw3d */
#endif /* GLOBJMANAGER_H_ */
