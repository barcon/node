#ifndef NODES_TYPES_HPP_
#define NODES_TYPES_HPP_

#include "utils.hpp"
#include "logger.hpp"
#include "eilig.hpp"

#include <memory>
#include <vector>

namespace dive
{
	namespace elements
	{
		class IElement;
		using IElementPtr = std::shared_ptr< IElement >;
		using ConstIElementPtr = std::shared_ptr< const IElement >;
	}
}

namespace nodes
{
	using Scalar = eilig::Scalar;
	using Vector = eilig::Vector;
	using Matrix = eilig::Matrix;

	using Number = std::size_t;
	using NumberDof = Number;

	using Index = eilig::Index;
	using DofIndex = Index;

	using Matrices = std::vector<Matrix>;
	using String = utils::String;
	using Tag = std::size_t;
	using Dimension = std::size_t;

	using IElementPtr = dive::elements::IElementPtr;
	using Elements = std::vector<IElementPtr>;

	const String headerNode = "NODE";

	class INode;
	using INodePtr = std::shared_ptr< INode >;
	using ConstINodePtr = std::shared_ptr< const INode >;

	class INode
	{
	public:
		virtual ~INode() = default;

		virtual const Vector& GetPoint() const = 0;
		virtual const Matrix& GetValue() const = 0;
		virtual Scalar GetValue(DofIndex dofIndex) const = 0;
		virtual Tag	GetTag() const = 0;

		virtual void SetPoint(Scalar x, Scalar y, Scalar z) = 0;
		virtual void SetPoint(const Vector& point) = 0;
		virtual void SetValue(const Matrix& value) = 0;
		virtual void SetValue(DofIndex dofIndex, Scalar value) = 0;
		virtual void SetTag(Tag tag) = 0;
		virtual void SetNodeIndex(const Index& index) = 0;
		virtual void SetNumberDof(const NumberDof& numberDof) = 0;

		virtual Index GetNodeIndex() const = 0;
		virtual NumberDof GetNumberDof() const = 0;

		virtual const Elements& GetElements() const = 0;
		virtual void AddElement(IElementPtr element) = 0;
		virtual void RemoveElement(IElementPtr element) = 0;
		virtual void ClearElements() = 0;

	protected:
		INode() = default;
	};

	using Nodes = std::vector<INodePtr>;

} // namespace nodes

#endif /* NODES_TYPES_HPP_*/