#include "node_basic.hpp"

namespace node
{
	NodePtr CreateNode(Tag tag)
	{
		auto res = Node::Create(tag, 3);


		return res;
	}
	NodePtr CreateNode(Tag tag, Scalar x)
	{
		auto res = Node::Create(tag, 1);

		res->SetPoint(0, x);

		return res;
	}
	NodePtr CreateNode(Tag tag, Scalar x, Scalar y)
	{
		auto res = Node::Create(tag, 2);

		res->SetPoint(0, x);
		res->SetPoint(1, y);

		return res;
	}
	NodePtr CreateNode(Tag tag, Scalar x, Scalar y, Scalar z)
	{
		auto res = Node::Create(tag, 3);

		res->SetPoint(0, x);
		res->SetPoint(1, y);
		res->SetPoint(2, z);

		return res;
	}
	NodePtr CreateNode(Tag tag, const Vector& point)
	{
		NumberCoordinates numberCoordinates = point.GetRows();

		if(numberCoordinates == 0)
		{
			logger::Error(headerNode, "Size of point vector not compatible");
			return nullptr;
		}

		auto res = Node::Create(tag, numberCoordinates);

		res->SetPoint(point);

		return res;
	}
	NodePtr CreateNode(Tag tag, const Vector& point, const Matrix& value)
	{
		NumberCoordinates numberCoordinates = point.GetRows();

		if (numberCoordinates == 0)
		{
			logger::Error(headerNode, "Size of point vector not compatible");
			return nullptr;
		}

		auto res = Node::Create(tag, numberCoordinates);

		res->SetPoint(point);
		res->SetValue(value);

		return res;
	}

	Nodes CreateNodes(const Matrix& input, NumberCoordinates numberCoordinates)
	{
		auto rows = input.GetRows();
		auto cols = input.GetCols();

		Matrix value;
		Nodes nodes;
		NodePtr node{ nullptr };
		Vector point;
		
		if ((numberCoordinates < 1) || (numberCoordinates > 3))
		{
			logger::Error(headerNode, "Incompatible dimension, 0 < number dimensions < 4");
			return nodes;
		}

		if (cols < (numberCoordinates + 1))
		{
			logger::Error(headerNode, utils::string::Format("Incompatible matrix size, columns < {}", numberCoordinates + 1));
			return nodes;
		}

		if (rows < 1)
		{
			logger::Error(headerNode, "Incompatible matrix size, rows < 1");
			return nodes;
		}

		value.Resize(1, cols - numberCoordinates);

		for (std::size_t i = 0; i < rows; ++i)
		{
			for (std::size_t j = 0; j < (cols - numberCoordinates); ++j)
			{
				value(0, j) = input(i, j + numberCoordinates);
			}

			switch (numberCoordinates)
			{
			case 1:
				node = node::CreateNode(i, input(i, 0));
				break;
			case 2:
				node = node::CreateNode(i, input(i, 0), input(i, 1));
				break;
			case 3:
				node = node::CreateNode(i, input(i, 0), input(i, 1), input(i, 2));
				break;
			}

			node->SetValue(value);
			nodes.push_back(node);
		}

		return nodes;
	}
	
	NodePtr Node::Create(Tag tag, NumberCoordinates numberCoordinates)
	{
		class MakeSharedEnabler : public Node
		{
		};

		if (numberCoordinates == 0)
		{
			throw std::invalid_argument("Number of coordinates equal to zero (Create Node)");
		}

		auto res = std::make_shared<MakeSharedEnabler>();

		res->SetTag(tag);
		res->SetNumberDof(1);
		res->point_ = Vector(numberCoordinates, 0.0);

		return res;
	}

	const Vector& Node::GetPoint() const
	{
		return point_;
	}
	const Matrix& Node::GetValue() const
	{
		return value_;
	}
	NumberCoordinates Node::GetNumberCoordinates() const
	{
		return point_.GetRows();
	}
	Scalar Node::GetValue(DofIndex dofIndex) const
	{
		return value_(dofIndex);
	}
	NumberDof Node::GetNumberDof() const
	{
		return value_.GetData().size();
	}
	Connectivity& Node::GetConnectivity()
	{
		return connectivity_;
	}
	Tag Node::GetTag() const
	{
		return tag_;
	}
	
	void Node::SetPoint(CoordinateIndex coordinateIndex, Scalar value)
	{
		if (coordinateIndex >= GetNumberCoordinates())
		{
			throw std::out_of_range("Coordinate index out of bounds (SetPoint)");
		}

		point_(coordinateIndex) = value;
	}
	void Node::SetPoint(const Vector& point)
	{
		if (point.GetRows() != point_.GetRows())
		{
			throw std::invalid_argument("Size of point vector not compatible (SetPoint)");
		}

		point_ = point;
	}
	void Node::SetValue(DofIndex dofIndex, Scalar value)
	{
		if(dofIndex >= GetNumberDof())
		{
			throw std::out_of_range("Dof index out of bounds (SetValue)");
		}

		value_(dofIndex) = value;
	}
	void Node::SetValue(const Matrix& value)
	{
		if (value.GetRows() == 0 || value.GetCols() == 0)
		{
			throw std::invalid_argument("Size of value matrix not compatible (SetValue)");
		}

		value_ = value;
	}
	void Node::SetTag(Tag tag)
	{
		tag_ = tag;
	}
	void Node::SetNumberDof(const NumberDof& numberDof)
	{
		if (numberDof == 0)
		{
			throw std::invalid_argument("Number of dof equal to zero (SetNumberDof)");
		}

		SetValue(Matrix(numberDof, 1, eilig::matrix_zeros));
	}
} //namespace node