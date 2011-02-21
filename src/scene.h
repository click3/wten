
namespace wten {

class Error;
class PTData;

/**
 * �Q�[���̏I���𖾎����邽�߂̃N���X
 * ���̃N���X���̂ɂ͉��̋@�\������
 */
class SceneExit {};

class Scene : boost::noncopyable {
public:
	virtual ~Scene() { }
	virtual boost::optional<boost::shared_ptr<Error> > DoStart(boost::shared_ptr<PTData> pt) = 0;
	virtual boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > DoNextFrame(void) = 0;
};

} // wten
