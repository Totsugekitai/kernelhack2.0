/*
 * Copyright 2009, Ingo Weinhold, ingo_weinhold@gmx.de.
 * Copyright 2013, Rene Gollent, rene@gollent.com.
 * Distributed under the terms of the MIT License.
 */
#ifndef SOURCE_VIEW_H
#define SOURCE_VIEW_H


#include <Font.h>
#include <View.h>

#include "Types.h"


class Breakpoint;
class FunctionInstance;
class SourceCode;
class StackFrame;
class StackTrace;
class Statement;
class SyntaxHighlightInfo;
class Team;
class Thread;
class UserBreakpoint;


class SourceView : public BView {
public:
	class Listener;

public:
								SourceView(Team* team, Listener* listener);
								~SourceView();

	static	SourceView*			Create(Team* team, Listener* listener);
									// throws

	virtual	void				MessageReceived(BMessage* message);

			void				UnsetListener();

			void				SetStackTrace(StackTrace* stackTrace,
									Thread* thread);
			void				SetStackFrame(StackFrame* stackFrame);
			void				SetSourceCode(SourceCode* sourceCode);

			void				UserBreakpointChanged(
									UserBreakpoint* breakpoint);

			bool				ScrollToAddress(target_addr_t address);
			bool				ScrollToLine(uint32 line);

			void				HighlightBorder(bool state);
	virtual	void				TargetedByScrollView(BScrollView* scrollView);

	virtual	BSize				MinSize();
	virtual	BSize				MaxSize();
	virtual	BSize				PreferredSize();

	virtual	void				DoLayout();

private:
			class BaseView;
			class MarkerManager;
			class MarkerView;
			class TextView;

			// for gcc2
			friend class TextView;
			friend class MarkerView;

			struct FontInfo {
				BFont		font;
				font_height	fontHeight;
				float		lineHeight;
			};

protected:
			bool				GetStatementForLine(int32 line,
									Statement*& _statement);

private:
			void				_Init();
			void				_UpdateScrollBars();
			BSize				_DataRectSize() const;

private:
			Team*				fTeam;
			Thread*				fActiveThread;
			StackTrace*			fStackTrace;
			StackFrame*			fStackFrame;
			SourceCode*			fSourceCode;
			MarkerManager*		fMarkerManager;
			MarkerView*			fMarkerView;
			TextView*			fTextView;
			FontInfo			fFontInfo;
			Listener*			fListener;
			SyntaxHighlightInfo* fCurrentSyntaxInfo;
};


class SourceView::Listener {
public:
	virtual						~Listener();

	virtual	void				SetBreakpointRequested(
									target_addr_t address, bool enabled) = 0;
	virtual	void				ClearBreakpointRequested(
									target_addr_t address) = 0;
	virtual void				ThreadActionRequested(Thread* thread,
									uint32 action, target_addr_t address) = 0;
	virtual	void				FunctionSourceCodeRequested(
									FunctionInstance* function,
									bool forceDisassembly) = 0;
};


#endif	// SOURCE_VIEW_H
