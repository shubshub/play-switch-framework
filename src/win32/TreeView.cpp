#include <assert.h>
#include "win32/TreeView.h"

using namespace Framework;
using namespace Framework::Win32;

CTreeView::CTreeView(HWND hParent, RECT* pR, unsigned long nStyle, unsigned long nExStyle)
{
	InitCommonControls();
	Create(nExStyle, WC_TREEVIEW, _T(""), WS_CHILD | WS_VISIBLE | nStyle, pR, hParent, NULL);
}

HTREEITEM CTreeView::InsertItem(TVINSERTSTRUCT* pI)
{
	return TreeView_InsertItem(m_hWnd, pI);
}

HTREEITEM CTreeView::InsertItem(HTREEITEM nParent, const TCHAR* sText)
{
	TVINSERTSTRUCT s;
	s.hParent		= nParent;
	s.hInsertAfter	= TVI_LAST;
	s.item.pszText	= const_cast<TCHAR*>(sText);
	s.item.mask		= TVIF_TEXT;
	return InsertItem(&s);
}

HTREEITEM CTreeView::GetSelection()
{
	return (HTREEITEM)TreeView_GetSelection(m_hWnd);
}

bool CTreeView::GetItem(HTREEITEM hItem, TVITEM* pI)
{
	pI->hItem = hItem;
	return ((TreeView_GetItem(m_hWnd, pI) == TRUE) ? true : false);
}

HTREEITEM CTreeView::GetItemParent(HTREEITEM hItem)
{
    return TreeView_GetParent(m_hWnd, hItem);
}

void CTreeView::GetItemText(HTREEITEM hItem, TCHAR* sText, size_t nCount)
{
	TVITEM Item;

	memset(&Item, 0, sizeof(TVITEM));
	Item.mask		= TVIF_TEXT;
	Item.pszText	= sText;
	Item.cchTextMax = static_cast<int>(nCount);

	GetItem(hItem, &Item);
}

void* CTreeView::GetItemParam(HTREEITEM hItem)
{
    TVITEM Item;

    memset(&Item, 0, sizeof(TVITEM));
    Item.mask       = TVIF_PARAM;

    GetItem(hItem, &Item);

    return reinterpret_cast<void*>(Item.lParam);
}

void CTreeView::GetItemLabelRect(HTREEITEM hItem, RECT* pRect)
{
	assert(pRect != NULL);
	TreeView_GetItemRect(m_hWnd, hItem, pRect, TRUE);
}

void CTreeView::SetItem(HTREEITEM hItem, TVITEM* pI)
{
	pI->hItem = hItem;
    TreeView_SetItem(m_hWnd, pI);
}

void CTreeView::SetItemText(HTREEITEM hItem, const TCHAR* sText)
{
    TVITEM Item;

    memset(&Item, 0, sizeof(TVITEM));
    Item.mask       = TVIF_TEXT;
    Item.pszText    = const_cast<TCHAR*>(sText);

    SetItem(hItem, &Item);
}

void CTreeView::SetItemParam(HTREEITEM hItem, void* pParam)
{
    TVITEM Item;

    memset(&Item, 0, sizeof(TVITEM));
    Item.mask       = TVIF_PARAM;
    Item.lParam     = reinterpret_cast<LPARAM>(pParam);

    SetItem(hItem, &Item);
}

void CTreeView::SetItemParam(HTREEITEM hItem, unsigned int nParam)
{
    TVITEM Item;

    memset(&Item, 0, sizeof(TVITEM));
    Item.mask       = TVIF_PARAM;
    Item.lParam     = nParam;

    SetItem(hItem, &Item);
}

HTREEITEM CTreeView::GetRoot()
{
	return TreeView_GetRoot(m_hWnd);
}

bool CTreeView::SetSelection(HTREEITEM hItem)
{
	return ((TreeView_SelectItem(m_hWnd, hItem) == TRUE) ? true : false);
}

bool CTreeView::Expand(HTREEITEM hItem, unsigned int nFlags)
{
	return ((TreeView_Expand(m_hWnd, hItem, nFlags) == TRUE) ? true : false);
}

bool CTreeView::DeleteAllItems()
{
	return ((TreeView_DeleteAllItems(m_hWnd) == TRUE) ? true : false);
}
