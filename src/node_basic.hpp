#ifndef NODE_BASIC_HPP_
#define NODE_BASIC_HPP_

#include "node_types.hpp"

namespace node
{
	class Node;
	using NodePtr = std::shared_ptr< Node >;
	using ConstNodePtr = std::shared_ptr< const Node >;

	NodePtr CreateNode(Tag tag);
	NodePtr CreateNode(Tag tag, Scalar x);
	NodePtr CreateNode(Tag tag, Scalar x, Scalar y);
	NodePtr CreateNode(Tag tag, Scalar x, Scalar y, Scalar z);
	NodePtr CreateNode(Tag tag, const Vector& point);
	NodePtr CreateNode(Tag tag, const Vector& point, const Matrix& value);

	Nodes	CreateNodes(const Matrix& input, NumberCoordinates numberCoordinates);

	class Node : public INode, virtual public std::enable_shared_from_this<Node>
	{
	public:
		virtual ~Node() = default;

		static NodePtr Create(Tag tag, NumberCoordinates numberCoordinates);

		const Vector& GetPoint() const override;
		const Matrix& GetValue() const override;
		NumberCoordinates GetNumberCoordinates() const override;
		NumberDof GetNumberDof() const override;
		Scalar GetValue(DofIndex dofIndex) const override;
		Connectivity& GetConnectivity() override;
		Tag	GetTag() const override;

		void SetPoint(CoordinateIndex coordinateIndex, Scalar value) override;
		void SetPoint(const Vector& point) override;
		void SetValue(DofIndex dofIndex, Scalar value) override;
		void SetValue(const Matrix& value) override;
		void SetTag(Tag tag) override;
		void SetNumberDof(const NumberDof& numberDof) override;
		

	protected:
		Node() = default;
		
		void SetNumberCoordinates(const NumberCoordinates& numberCoordinates);

		Vector point_;
		Matrix value_;
		Tag	tag_{ 0 };

		Connectivity connectivity_;
	};
} // namespace node

#endif /* NODE_BASIC_HPP_*/