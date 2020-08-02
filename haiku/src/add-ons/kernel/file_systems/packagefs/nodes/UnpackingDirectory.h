/*
 * Copyright 2009-2013, Ingo Weinhold, ingo_weinhold@gmx.de.
 * Distributed under the terms of the MIT License.
 */
#ifndef UNPACKING_DIRECTORY_H
#define UNPACKING_DIRECTORY_H


#include "Directory.h"
#include "PackageDirectory.h"
#include "UnpackingNode.h"


class UnpackingDirectory : public Directory, public UnpackingNode {
public:
								UnpackingDirectory(ino_t id);
	virtual						~UnpackingDirectory();

	virtual	status_t			VFSInit(dev_t deviceID);
	virtual	void				VFSUninit();

	virtual	mode_t				Mode() const;
	virtual	uid_t				UserID() const;
	virtual	gid_t				GroupID() const;
	virtual	timespec			ModifiedTime() const;
	virtual	off_t				FileSize() const;

	virtual	Node*				GetNode();

	virtual	status_t			AddPackageNode(PackageNode* packageNode,
									dev_t deviceID);
	virtual	void				RemovePackageNode(PackageNode* packageNode,
									dev_t deviceID);

	virtual	PackageNode*		GetPackageNode();
	virtual	bool				IsOnlyPackageNode(PackageNode* node) const;
	virtual	bool				WillBeFirstPackageNode(
									PackageNode* packageNode) const;

	virtual	void				PrepareForRemoval();

	virtual	status_t			OpenAttributeDirectory(
									AttributeDirectoryCookie*& _cookie);
	virtual	status_t			OpenAttribute(const StringKey& name,
									int openMode, AttributeCookie*& _cookie);

	virtual	status_t			IndexAttribute(AttributeIndexer* indexer);
	virtual	void*				IndexCookieForAttribute(const StringKey& name)
									const;

private:
			PackageDirectoryList fPackageDirectories;
};


class RootDirectory : public UnpackingDirectory {
public:
								RootDirectory(ino_t id,
									const timespec& modifiedTime);

	virtual	timespec			ModifiedTime() const;

private:
			timespec			fModifiedTime;
};


#endif	// UNPACKING_DIRECTORY_H
