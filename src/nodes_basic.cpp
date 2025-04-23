#include "nodes_basic.hpp"

namespace nodes
{
	NodePtr CreateNode()
	{
		auto res = Node::Create();

		return res;
	}
	NodePtr CreateNode(Tag nodeTag)
	{
		auto res = Node::Create();

		res->SetTag(nodeTag);

		return res;
	}
	NodePtr CreateNode(Tag nodeTag, Scalar x, Scalar y, Scalar z)
	{
		auto res = CreateNode();

		res->SetTag(nodeTag);
		res->SetPoint(x, y, z);

		return res;
	}
	NodePtr CreateNode(Tag nodeTag, Scalar x, Scalar y, Scalar z, Scalar value)
	{
		auto res = CreateNode();

		res->SetTag(nodeTag);
		res->SetPoint(x, y, z);
		res->SetValue(0, value);

		return res;
	}
	NodePtr CreateNode(Tag nodeTag, const Vector& point)
	{
		auto res = CreateNode();

		res->SetTag(nodeTag);
		res->SetPoint(point);

		return res;
	}
	NodePtr CreateNode(Tag nodeTag, const Vector& point, const Matrix& value)
	{
		auto res = CreateNode();

		res->SetTag(nodeTag);
		res->SetPoint(point);
		res->SetValue(value);

		return res;
	}	
	NodePtr CreateNode(Scalar x, Scalar y, Scalar z)
	{
		auto res = CreateNode();

		res->SetPoint(x, y, z);

		return res;
	}
	NodePtr CreateNode(Scalar x, Scalar y, Scalar z, Scalar value)
	{
		auto res = CreateNode();

		res->SetPoint(x, y, z);
		res->SetValue(0, value);

		return res;
	}
	NodePtr CreateNode(const Vector& point)
	{
		auto res = CreateNode();

		res->SetPoint(point);

		return res;
	}
	NodePtr CreateNode(const Vector& point, const Matrix& value)
	{
		auto res = CreateNode();

		res->SetPoint(point);
		res->SetValue(value);

		return res;
	}
	
	Nodes	CreateNodes(const Matrix& input, Dimension dim)
	{
		auto rows = input.GetRows();
		auto cols = input.GetCols();

		Matrix value;
		Nodes nodes;
		NodePtr node{ nullptr };
		
		if ((dim < 1) || (dim > 3))
		{
			logger::Error(headerNode, "Incompatible dimension, 0 < dim < 4");
			return nodes;
		}

		if (cols < (dim + 1))
		{
			logger::Error(headerNode, "Incompatible matrix size, columns < %u", dim + 1);
			return nodes;
		}

		if (rows < 1)
		{
			logger::Error(headerNode, "Incompatible matrix size, rows < 1");
			return nodes;
		}

		value.Resize(1, cols - dim);

		for (std::size_t i = 0; i < rows; ++i)
		{
			for (std::size_t j = 0; j < (cols - dim); ++j)
			{
				value(0, j) = input(i, j + dim);
			}

			switch (dim)
			{
			case 1:
				node = nodes::CreateNode(input(i, 0), 0.0, 0.0);
				break;
			case 2:
				node = nodes::CreateNode(input(i, 0), input(i, 1), 0.0);
				break;
			case 3:
				node = nodes::CreateNode(input(i, 0), input(i, 1), input(i, 2));
				break;
			}

			node->SetTag(i);
			node->SetValue(value);
			nodes.push_back(node);
		}

		return nodes;
	}
	
	Node::Node()
	{
		SetPoint(Vector(3, 0.0));
		SetNumberDof(1);
	}
	NodePtr Node::Create()
	{
		class MakeSharedEnabler : public Node
		{
		};

		auto res = std::make_shared<MakeSharedEnabler>();

		return res;
	}
	NodePtr Node::GetPtr()
	{
		return std::dynamic_pointer_cast<Node>(shared_from_this());
	}
	ConstNodePtr Node::GetPtr() const
	{
		return const_cast<Node*>(this)->GetPtr();
	}

	const Vector& Node::GetPoint() const
	{
		return point_;
	}
	const Matrix& Node::GetValue() const
	{
		return value_;
	}
	Scalar Node::GetValue(DofIndex dofIndex) const
	{
		return value_(dofIndex);
	}
	Tag Node::GetTag() const
	{
		return tag_;
	}
	
	void Node::SetPoint(Scalar x, Scalar y, Scalar z)
	{
		point_(0) = x;
		point_(1) = y;
		point_(2) = z;
	}
	void Node::SetPoint(const Vector& point)
	{
		if (point.GetRows() != 3)
		{
			logger::Error(headerNode, "Number of dof equal to zero");
			return;
		}

		point_ = point;
	}
	void Node::SetValue(const Matrix& value)
	{
		value_ = value;
	}
	void Node::SetValue(DofIndex dofIndex, Scalar value)
	{
		value_(dofIndex) = value;
	}
	void Node::SetTag(Tag tag)
	{
		tag_ = tag;
	}
	void Node::SetNodeIndex(const Index& index)
	{
		index_ = index;
	}
	void Node::SetNumberDof(const NumberDof& numberDof)
	{
		if (numberDof == 0)
		{
			logger::Error(headerNode,"Number of dof equal to zero");
			return;
		}

		if (numberDof != GetNumberDof())
		{
			SetValue(Matrix(numberDof, 1, 0.0));
		}
	}

	Index Node::GetNodeIndex() const
	{
		return index_;
	}
	NumberDof Node::GetNumberDof() const
	{
		return value_.GetData().size();
	}

	const Elements& Node::GetElements() const
	{
		return elements_;
	}
	void Node::AddElement(IElementPtr element)
	{
		auto it = std::find(elements_.begin(), elements_.end(), element);

		if (it == elements_.end())
		{
			elements_.push_back(element);
		}
	}
	void Node::RemoveElement(IElementPtr element)
	{
		auto it = std::find(elements_.begin(), elements_.end(), element);

		if (it != elements_.end())
		{
			elements_.erase(it);
		}
	}
	void Node::ClearElements()
	{
		elements_.clear();
	}
} //namespace nodes