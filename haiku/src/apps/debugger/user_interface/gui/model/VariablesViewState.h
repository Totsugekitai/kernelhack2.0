/*
 * Copyright 2013-2018, Rene Gollent, rene@gollent.com.
 * Copyright 2009, Ingo Weinhold, ingo_weinhold@gmx.de.
 * Distributed under the terms of the MIT License.
 */
#ifndef VARIABLES_VIEW_STATE_H
#define VARIABLES_VIEW_STATE_H


#include <Message.h>
#include <Referenceable.h>
#include <util/OpenHashTable.h>


class ExpressionValues;
class ObjectID;
class StackFrameValues;
class Type;
class TypeComponentPath;
class TypeHandler;


class VariablesViewNodeInfo {
public:
								VariablesViewNodeInfo();
								VariablesViewNodeInfo(
									const VariablesViewNodeInfo& other);
	virtual						~VariablesViewNodeInfo();

			VariablesViewNodeInfo& operator=(
									const VariablesViewNodeInfo& other);

			bool				IsNodeExpanded() const
									{ return fNodeExpanded; }
			void				SetNodeExpanded(bool expanded);

			Type*				GetCastedType() const
									{ return fCastedType; }
			void				SetCastedType(Type* type);

			TypeHandler*		GetTypeHandler() const
									{ return fTypeHandler; }
			void				SetTypeHandler(TypeHandler* handler);


			const BMessage&		GetRendererSettings() const
									{ return fRendererSettings; }

			void				SetRendererSettings(const BMessage& settings);

private:
			bool				fNodeExpanded;
			Type*				fCastedType;
			TypeHandler*		fTypeHandler;
			BMessage			fRendererSettings;
};


class VariablesViewState : public BReferenceable {
public:
								VariablesViewState();
	virtual						~VariablesViewState();

			status_t			Init();

			StackFrameValues*	Values() const
									{ return fValues; }
			void				SetValues(StackFrameValues* values);

			ExpressionValues*	GetExpressionValues() const
									{ return fExpressionValues; }
			void				SetExpressionValues(ExpressionValues* values);

			const VariablesViewNodeInfo* GetNodeInfo(ObjectID* variable,
									const TypeComponentPath* path) const;
	inline	const VariablesViewNodeInfo* GetNodeInfo(ObjectID* variable,
									const TypeComponentPath& path) const;

			status_t			SetNodeInfo(ObjectID* variable,
									TypeComponentPath* path,
									const VariablesViewNodeInfo& info);
									// requires an on-heap path

private:
			struct Key;
			struct InfoEntry;
			struct InfoEntryHashDefinition;

			typedef BOpenHashTable<InfoEntryHashDefinition> NodeInfoTable;

private:
			void				_Cleanup();

private:
			NodeInfoTable*		fNodeInfos;
			StackFrameValues*	fValues;
			ExpressionValues*	fExpressionValues;
};


const VariablesViewNodeInfo*
VariablesViewState::GetNodeInfo(ObjectID* variable,
	const TypeComponentPath& path) const
{
	return GetNodeInfo(variable, &path);
}


#endif	// VARIABLES_VIEW_STATE_H
