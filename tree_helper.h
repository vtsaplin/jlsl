#ifndef __tree_helper_h__
#define __tree_helper_h__

template<class T> 
class tree_helper {
protected:
	tree_helper * _head, * _tail;
	tree_helper * _prev, * _next;
	tree_helper * _parent;

public:
	tree_helper () {
		_head = _tail = _prev = _next = _parent = 0;
	}
	virtual ~tree_helper () {
		detach ();
		delete_children ();
	}
	void attach (T * obj) {
		attach_to_tail (obj);
	}
	void attach_to_head (T * obj) {
		if (obj->_prev || obj->_next || obj->_parent) {
			obj->detach ();
		}
		if (_head) {
			_head->_prev = obj;
			obj->_next = _head;
		} else {
			_tail = obj;
		}
		obj->_parent = (this);
		_head = obj;
	}
	void attach_to_tail (T * obj) {
		if (obj->_prev || obj->_next || obj->_parent) {
			obj->detach ();
		}
		if (_tail) {
			_tail->_next = obj;
			obj->_prev = _tail;
		} else {
			_head = obj;
		}
		obj->_parent = (this);
		_tail = obj;
	}
	void insert_before (T * obj) {
		if (obj->_prev || obj->_next || obj->_parent) {
			obj->detach ();
		}
		if (_prev) {
			_prev->_next = obj;
			obj->_prev = _prev;
		}
		obj->_next = (this);
		_prev = obj;
		if (_parent) {
			if (_parent->_head == (this)) {
				_parent->_head = obj;
			}
			obj->_parent = _parent;
		}
	}
	void insert_after (T * obj) {
		if (obj->_prev || obj->_next || obj->_parent) {
			obj->detach ();
		}
		if (_next) {
			_next->_prev = obj;
			obj->_next = _next;
		}
		obj->_prev = (this);
		_next = obj;
		if (_parent) {
			if (_parent->_tail == (this)) {
				_parent->_tail = obj;
			}
			obj->_parent = _parent;
		}
	}
	void detach () {
		if (_parent) {
			if (_parent->_head == (this)) {
				if (_next) {
					_parent->_head = _next;
				} else {
					_parent->_head = _parent->_tail = 0;
				}
			} else if (_parent->_tail == (this)) {
				if (_prev) {
					_parent->_tail = _prev;
				}
			}
		}
		if (_prev) {
			_prev->_next = _next;
		}
		if (_next) {
			_next->_prev = _prev;
		}
		_prev = _next = _parent = 0;
	}
	void delete_children () {
		while (get_head ()) {
			delete get_head ();
		}
	}
	T * get_head () {
		return (T *)_head;
	}
	T * get_tail () {
		return (T *)_tail;
	}
	T * get_prev () {
		return (T *)_prev;
	}
	T * get_next () {
		return (T *)_next;
	}
	T * get_parent () {
		return (T *)_parent;
	}
	int get_count () {
		int total = 0;
		tree_helper * p = get_head ();
		while (p) {
			total++;
			p = p->get_next ();
		}
		return total;
	}
};

#endif /* __tree_helper_h__ */
