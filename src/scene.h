
namespace wten {

class Error;
class PTData;

/**
 * �Q�[���̏I���𖾎����邽�߂̃N���X
 * ���̃N���X���̂ɂ͉��̋@�\������
 */
class SceneExit {};

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class Scene : boost::noncopyable {
public:
	virtual ~Scene() { }
	virtual boost::optional<boost::shared_ptr<Error> > DoStart(boost::shared_ptr<PTData> pt) = 0;
	virtual boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > DoNextFrame(void) = 0;
};
#pragma warning(pop)

} // wten
