
// kursachDoc.h : interface of the CkursachDoc class
//


#pragma once
class CMyTreeView;
class CkursachView;

class CkursachDoc : public CDocument
{
protected: // create from serialization only
	CkursachDoc() noexcept;
	DECLARE_DYNCREATE(CkursachDoc)

// Attributes
public:
	CMyTreeView* pTree;
	CkursachView* pView;
	void DisplayImageForFirstIsp();
	void DisplayImageForSecondIsp();

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CkursachDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
