// libraryfeature.h
// Created 8/17/2009 by RJ Ryan (rryan@mit.edu)

#ifndef LIBRARYFEATURE_H
#define LIBRARYFEATURE_H

#include <QtDebug>
#include <QIcon>
#include <QModelIndex>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QAbstractItemModel>
#include <QUrl>

#include "trackinfoobject.h"
#include "treeitemmodel.h"

class TrackModel;
class WLibrarySidebar;
class WLibrary;
class MixxxKeyboard;

class LibraryFeature : public QObject {
  Q_OBJECT
  public:
    LibraryFeature(QObject* parent = NULL);

    virtual QVariant title() = 0;
    virtual QIcon getIcon() = 0;

    virtual bool dropAccept(QList<QUrl> urls) = 0;
    virtual bool dropAcceptChild(const QModelIndex& index, QList<QUrl> urls) = 0;
    virtual bool dragMoveAccept(QUrl url) = 0;
    virtual bool dragMoveAcceptChild(const QModelIndex& index, QUrl url) = 0;

    // Reimplement this to register custom views with the library widget.
    virtual void bindWidget(WLibrary* /* libraryWidget */,
                            MixxxKeyboard* /* keyboard */) {
    }
    virtual TreeItemModel* getChildModel() = 0;

  public slots:
    /** called when you single click on the root item **/
    virtual void activate() = 0;
    /** called when you single click on a child item, e.g., a concrete playlist or crate **/
    virtual void activateChild(const QModelIndex& index) = 0;
    /** called when you right click on the root item **/
    virtual void onRightClick(const QPoint& globalPos) = 0;
    /** called when you right click on a child item, e.g., a concrete playlist or crate **/
    virtual void onRightClickChild(const QPoint& globalPos, QModelIndex index) = 0;
    /*
     * Only implement this, if using incremental or lazy childmodels, see BrowseFeature.
     * This method is executed whenever you **double** click child items
     */
    virtual void onLazyChildExpandation(const QModelIndex& index) = 0;
  signals:
    void showTrackModel(QAbstractItemModel* model);
    void switchToView(const QString& view);
    void loadTrack(TrackPointer pTrack);
    void loadTrackToPlayer(TrackPointer pTrack, QString group);
    void restoreSearch(const QString&);
    /** emit this signal before you parse a large music collection, e.g., iTunes, Traktor. **/
    void featureIsLoading(LibraryFeature*);
    /** emit this signal if the foreign music collection has been imported/parsed. **/
    void featureLoadingFinished(LibraryFeature*s);
    /** emit this signal to select pFeature **/
    void featureSelect(LibraryFeature* pFeature, const QModelIndex& index);

};

#endif /* LIBRARYFEATURE_H */
