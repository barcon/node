#ifndef NODES_BASIC_HPP_
#define NODES_BASIC_HPP_

#include "nodes_types.hpp"

namespace nodes
{
	class Node;
	using NodePtr = std::shared_ptr< Node >;
	using ConstNodePtr = std::shared_ptr< const Node >;

	NodePtr CreateNode();
	NodePtr CreateNode(Tag nodeTag);
	NodePtr CreateNode(Tag nodeTag, Scalar x, Scalar y, Scalar z);
	NodePtr CreateNode(Tag nodeTag, Scalar x, Scalar y, Scalar z, Scalar value);
	NodePtr CreateNode(Tag nodeTag, const Vector& point);
	NodePtr CreateNode(Tag nodeTag, const Vector& point, const Matrix& value);

	NodePtr CreateNode(Scalar x, Scalar y, Scalar z);
	NodePtr CreateNode(Scalar x, Scalar y, Scalar z, Scalar value);
	NodePtr CreateNode(const Vector& point);
	NodePtr CreateNode(const Vector& point, const Matrix& value);
	
	Nodes	CreateNodes(const Matrix& input, Dimension dim);

	class Node : public INode, virtual public std::enable_shared_from_this<Node>
	{
	public:
		virtual ~Node() = default;

		static NodePtr Create();
		NodePtr GetPtr();
		ConstNodePtr GetPtr() const;

		const Vector& GetPoint() const override;
		const Matrix& GetValue() const override;
		Scalar GetValue(DofIndex dofIndex) const override;
		Tag	GetTag() const override;

		void SetPoint(Scalar x, Scalar y, Scalar z) override;
		void SetPoint(const Vector& point) override;
		void SetValue(const Matrix& value) override;
		void SetValue(DofIndex dofIndex, Scalar value) override;
		void SetTag(Tag tag) override;
		void SetNumberDof(const NumberDof& numberDof) override;
		
		NumberDof GetNumberDof() const override;
		Connectivity& GetConnectivity() override;

	protected:
		Node();

		Vector point_;
		Matrix value_;
		Index index_;
		Tag	tag_{ 0 };

		Connectivity connectivity_;
	};
} // namespace nodes

#endif /* NODES_BASIC_HPP_*/