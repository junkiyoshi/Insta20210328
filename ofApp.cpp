#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	vector<ofColor> base_color_list;
	ofColor color;
	vector<int> hex_list = { 0xef476f, 0xffd166, 0x06d6a0, 0x118ab2, 0x073b4c };
	for (auto hex : hex_list) {

		color.setHex(hex);
		base_color_list.push_back(color);
	}
	int color_index = 0;

	for (auto scale = 1; scale < 20; scale += 1) {

		ofMesh face, line;
		line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

		vector<glm::vec2> vertices;
		auto param = (ofGetFrameNum() * 3 + scale * 20) % 720;
		for (auto deg = 0; deg < 360; deg += 1) {

			if (param < 360) {

				if (deg < param) { vertices.push_back(this->make_point(deg * DEG_TO_RAD) * scale); }
			}
			else {

				if (deg > param - 360) { vertices.push_back(this->make_point(deg * DEG_TO_RAD) * scale); }
			}
		}

		for (auto& vertex : vertices){

			face.addVertex(glm::vec3(vertex, -15));
			face.addVertex(glm::vec3(vertex, 15));

			line.addVertex(glm::vec3(vertex, -15));
			line.addVertex(glm::vec3(vertex, 15));

			if (vertex != vertices.front()) {

				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 4);
				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

				line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 3);
				line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 4);
			}

			face.addColor(base_color_list[color_index]);
			face.addColor(base_color_list[color_index]);

			line.addColor(ofColor(39));
			line.addColor(ofColor(39));
		}

		line.addIndex(0); line.addIndex(1);
		line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 2);

		face.draw();
		line.drawWireframe();

		color_index = (color_index + 1) % base_color_list.size();
	}

	this->cam.end();
}

//--------------------------------------------------------------
//Reference by https://twitter.com/shiffman/status/1095764239665512453
glm::vec2 ofApp::make_point(float theta) {

	float x = 16 * (pow(sin(theta), 3));
	float y = 13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta);
	return glm::vec2(x, -y);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}