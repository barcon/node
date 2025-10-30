#ifndef NODE_TYPES_HPP_
#define NODE_TYPES_HPP_

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

namespace node
{
	using Scalar = eilig::Scalar;
	using Vector = eilig::Vector;
	using Matrix = eilig::Matrix;

	using Number = std::size_t;
	using NumberDof = Number;

	using Index = std::size_t;
	using Indices = std::vector<Index>;
	using DofIndex = Index;
	using DofIndices = std::vector<DofIndex>;

	using Matrices = std::vector<Matrix>;
	using String = utils::String;
	using Tag = std::size_t;
	using Dimension = std::size_t;
	
	const String headerNode = "NODE";

	using IElementPtr = dive::elements::IElementPtr;
	using Elements = std::vector<IElementPtr>;

	struct Connectivity {
		Index nodeIndex;
		DofIndices globalDofIndices;
		Elements elements;
	};

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

		virtual void SetPoint(Scalar x) = 0;
		virtual void SetPoint(Scalar x, Scalar y) = 0;
		virtual void SetPoint(Scalar x, Scalar y, Scalar z) = 0;
		virtual void SetPoint(const Vector& point) = 0;
		virtual void SetValue(const Matrix& value) = 0;
		virtual void SetValue(DofIndex dofIndex, Scalar value) = 0;
		virtual void SetTag(Tag tag) = 0;
		virtual void SetNumberDof(const NumberDof& numberDof) = 0;

		virtual NumberDof GetNumberDof() const = 0;
		virtual Connectivity& GetConnectivity() = 0;

	protected:
		INode() = default;
	};

	using Nodes = std::vector<INodePtr>;

} // namespace node

#endif /* NODE_TYPES_HPP_*/