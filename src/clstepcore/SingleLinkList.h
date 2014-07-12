#ifndef singlelinklist_h
#define singlelinklist_h

/*
* NIST STEP Core Class Library
* clstepcore/SingleLinkList.h
* April 1997
* David Sauder
* KC Morris

* Development of this software was funded by the United States Government,
* and is not subject to copyright.
*/

#include <sc_export.h>
#include <sc_mutex.h>

class SC_CORE_EXPORT SingleLinkList  {

        // node which represents the value is contained in the subclass
        //  since it may have different types for different lists

    protected:

        class  SingleLinkNode  * head;
        SingleLinkNode  * tail;
Made STEPaggregrate thread safe.

This was done by relying on the mtx used by its superclass: SingleLinkList.
    public:
        // had to be made into a pointer due to the equality
        //  operator being used elswhere for SingleLinkList object
        sc_recursive_mutex * mtxP; //making it public for the use in STEPaggregrate (where another object might lock/unlock them)

        virtual SingleLinkNode * NewNode();
        virtual void AppendNode( SingleLinkNode * );
        virtual void DeleteNode( SingleLinkNode * );

        virtual void Empty();
        virtual void DeleteFollowingNodes( SingleLinkNode * );
        virtual SingleLinkNode * GetHead() const;

        int EntryCount() const;

        SingleLinkList();
        virtual ~SingleLinkList();

}
;


class SC_CORE_EXPORT SingleLinkNode {
        friend class SingleLinkList;
    protected:

    public:
        SingleLinkList * owner;
        SingleLinkNode * next;

        virtual SingleLinkNode * NextNode() const;
        SingleLinkNode() : owner( 0 ), next( 0 )  { }
        virtual ~SingleLinkNode() { }

};

#endif
