/**
 *	sortable-list.js
 *
 *  sortable-list.js depends on jquery and jquery.ui
 **/

'use strict';

(function(window, $) {

	function SortableList(options) {
		return new SortableList.create(options)
	}

	/**
	 *	private
	 */


	/**
	 *	public
	 */
	SortableList.prototype = {

		// After document is ready, init() has to be called to invoke event listeners
		init: function(options) {
			// this.items stores the reference of array of objects such as favorites
			this.items = options.items || [];
			// this.tempItems is a temporary storage for updated this.items
			// Make this.tempItems a shallow copy of this.itmes
			this.tempItems = this.items.slice(0);
			// this.methods stores helper functions from outside of the module
			this.methods = options.methods || {};
			// event listeners
			this.events = options.events || {};
			// this.defaultAnimationDuration determines how long the animation will take
			// for instance, show, hide, fadeIn, fadeOut, etc
			this.defaultAnimationDuration = options.defaultAnimationDuration;

			// Create jQuery objects by using HTML ids and classes obtained from options
			this.$listSection = $('#' + this.listSectionId);
			this.$listHeader = $('#' + this.listHeaderId);
			this.$listUl = $('#' + this.listUlId);

			this.$detailSection = $('#' + this.detailSectionId);
			this.$detailHeader = $('#' + this.detailHeaderId);
			this.$detailArticle = $('#' + this.detailArticleId);
			this.$detailEditArticle = $('#' + this.detailEditArticleId);

			this.invokeEventListeners();
		},

		// Add eventListeners to this.events
		addEventListeners: function(newEvents) {
			$.extend(this.events, newEvents);
		},

		// Invoke the event listeners
		invokeEventListeners(events) {
			// If no events is given, this.events will be invoked
			events = events || this.events;
			for (var eventName in events) {
				console.log('Event listener, "' + eventName + '" is invoked.');
				this.events[eventName].call(this);
			}
		},

		// Create HTML elements and append them to this.$listHeader and this.$listUl
		resetListSection: function() {
			var self = this;

			// Remove all existing child nodes of this.$listHeader
			this.$listHeader.empty();
			console.log('empty this.$listHeader with id="' + this.listHeaderId + '"');

			// Remove all existing child nodes of this.$ul
			this.$listUl.empty();
			console.log('empty this.$listUl with id="' + this.listUlId + '"');

			// Create a header and append it to this.$listHeader
			this.$listHeader.append($(this.getListHeaderHtml()));

			// Create an array of li HTML strings iterating through this.items
			var arrayLiHtmls = this.items.map(function(item, index, items) {
				return self.getListLiHtml(index);
			});

			// Combine the array of li HTML to a string and append it to this.$listUl
			this.$listUl.append(arrayLiHtmls.join(''));
		},

		// Create HTML elements and append them to this.$detailArticle
		resetDetailArticle: function() {
			// Remove all existing child nodes of this.$detailArticle
			this.$detailArticle.empty();

			var strDetailHtml = this.getDetailArticleHtml();
			this.$detailArticle.append($(strDetailHtml));
		},

		// Create HTML elements for this.$detailEditArticle
		resetDetailEditArticle: function() {
			// Remove all existing child nodes of this.$detailEditArticle
			this.$detailEditArticle.empty();

			var strDetailEditHtml = this.getDetailEditArticleHtml();
			this.$detailEditArticle.append($(strDetailEditHtml));
		},

		// Set this.items point at newItems and Make this.tempItems a shallow copy of this.items
		setBothItems: function(newItems) {
			this.items = newItems;
			// Make this.tempItems a shallow copy of this.items
			this.tempItems = this.items.slice(0);
		},

		// Update the array, this.tempItems according to the changes on $listUl
		// such as the changes on the order and deletion of lis of $listUl
		saveListToTempItems: function() {
			var items = this.items;
			var tempItems = this.tempItems;
			var arrayLis = $.makeArray(this.$listUl.find('.' + this.listLiClass));
			var lisLength = arrayLis.length;
			var listDataId = this.listDataId;

			for (var i = 0; i < lisLength; i++) {
				// itemIndex stores the listDataId data attribute of each li
				var itemIndex = $(arrayLis[i]).data(listDataId);
				// Copy the reference of each rearranged item
				tempItems[i] = items[itemIndex];
			}
			// Removed the elements of items which have been removed from this.$listUl
			tempItems.splice(lisLength);
		},

		// Update one element of this.items accroding to the changes from the form inputs
		// and save this.items into database
		saveDetailToTempItems: function() {
			var item = this.tempItems[this.selectedItemIndex];

			// Turn an array-like jQuery object into an array
			var arrayInputs = $.makeArray(this.$detailEditArticle.find('input'));
			var inputsLength = arrayInputs.length;

			// Update the properties of the selected item
			// with input values of the form in #detailEditArticle
			for (var i = 0; i < inputsLength; i++) {
				var $input = $(arrayInputs[i]);
				var prop = $input.attr('name');
				item[prop] = $input.val();
			}

			// Turn an array-like jQuery object into an array
			var arrayTextareas = $.makeArray(this.$detailEditArticle.find('textarea'));
			var textareasLength = arrayTextareas.length;

			// Update the properties of the selected item
			// with textarea values of the form in #detailEditArticle
			for (var i = 0; i < textareasLength; i++) {
				var $textarea = $(arrayTextareas[i]);
				var prop = $textarea.attr('name');
				item[prop] = $textarea.val();
			}
		},

		hideList: function(animationDuration) {
			// animationDuration = animationDuration || this.defaultAnimationDuration;
			this.$listSection.hide(animationDuration);
		},

		hideDetail: function(animationDuration) {
			// animationDuration = animationDuration || this.defaultAnimationDuration;
			this.$detailArticle.hide(animationDuration);
		},

		hideDetailEdit: function(animationDuration) {
			// animationDuration = animationDuration || this.defaultAnimationDuration;
			this.$detailEditArticle.hide(animationDuration);
		},

		showList: function(animationDuration) {
			animationDuration = animationDuration || this.defaultAnimationDuration;
			this.hideDetail(animationDuration);
			this.hideDetailEdit(animationDuration);
			this.resetListSection();
			this.$listSection.show(animationDuration);
		},

		// Reset HTML detail contents and display the detail article
		showDetail: function(animationDuration) {
			animationDuration = animationDuration || this.defaultAnimationDuration;
			this.hideList(animationDuration);
			this.hideDetailEdit(animationDuration);
			// Show this.$detailSection and this.$detailArticle
			this.resetDetailArticle();
			this.$detailSection.show(animationDuration);
			this.$detailArticle.show(animationDuration);
		},

		// Display the edit form for the previously selected favorite detail
		showDetailEdit: function(animationDuration) {
			animationDuration = animationDuration || this.defaultAnimationDuration;
			this.hideList(animationDuration);
			this.hideDetail(animationDuration);
			this.resetDetailEditArticle();
			// Show this.$detailSection and this.$detailEditArticle
			this.$detailSection.show(animationDuration);
			this.$detailEditArticle.show(animationDuration);
		},

		// Make this.$ul sortable
		// callback is invoked whenever there is any changes on the order of this.$ul
		_enableListSortable: function(callback) {
			var self = this;

			this.$listUl.sortable({
				disabled: false,
				update: function() {
					// Update this.tempItems according to the changes on this.$listUl
					self.saveListToTempItems();
					if (callback) {
						callback.call(self);
					}
				}
			});

			// Disable selection of text content in this.$ul
			this.$listUl.disableSelection();
			console.log('SortableList is enabled');
		},

		// Make this.$ul unsortable
		_disableListSortable: function() {
			this.$listUl.sortable({
				disabled: true,
			});

			// Enable selection of text content in this$.ul
			this.$listUl.enableSelection();
			console.log('SortableList is disabled');
		}

		// // Find arrayMatchedLis which return true from callback and then
		// // invoke action with the passing parameter arrayMatchedLis[i]
		// findLis: function(callback, action) {
		//
		// 	var self = this;
		//
		// 	// Turn an array-like jQuery object into an array
		// 	var arrayLis = $.makeArray(this.$listUl.find('.' + this.listLiClass));
		// 	var lisLength = arrayLis.length;
		// 	var arrayMatchedLis = [];
		// 	var isMatched;
		//
		// 	for (var i = 0; i < lisLength; i++) {
		// 		isMatched = callback(arrayLis[i], i, arrayLis);
		// 		if (isMatched) {
		// 			// When callback return true, push arrayLis[i] to arrayMatchedLis
		// 			arrayMatchedLis.push(arrayLis[i]);
		// 		}
		// 	}
		//
		// 	// When action function is given
		// 	if (action) {
		// 		var matchedLisLength = arrayMatchedLis.length;
		// 		for (var i = 0; i < matchedLisLength; i++) {
		// 			action.call(self, arrayMatchedLis[i], i, arrayMatchedLis);
		// 		}
		// 	}
		//
		// },
		//
		// // Find matchedLis which returns true from callback and then
		// // remove the li and the corresponding item from this.items
		// removeLis: function(callback) {
		//
		// 	var self = this;
		//
		// 	this.findLis(callback, function(matchedLi) {
		// 		var $matchedLi = $(matchedLi);
		// 		// Get itemId from the data-id attribute of li
		// 		var itemId = $matchedLi.data(self.listDataId);
		//
		// 		// Remove the corresponding item from the this.items
		// 		self.items.splice(itemId, 1);
		// 		// Remove the matchedLi
		// 		$matchedLi.remove();
		//
		// 	});
		//
		// },
		//
		//
		// findLiById: function(itemIndex, action) {
		//
		// 	var self = this;
		//
		// 	this.findLis(function(li) {
		// 		// typeof id is number
		// 		var id = $(li).data(self.listDataId);
		// 		return id === itemIndex;
		// 	}, function(matchedLi) {
		// 		action.call(self, matchedLi);
		// 	});
		//
		// },
		//
		// removeLiById: function(itemIndex) {
		// 	var self = this;
		//
		// 	this.findLiById(itemIndex, function(matchedLi) {
		// 		// Remove the selected li
		// 		$(matchedLi).remove();
		// 		// Remove the corresponding item from this.items
		// 		self.items.splice(itemIndex, 1);
		// 	});
		// }

	};

	SortableList.create = function(options) {
		// list section
		this.listSectionId = options.listSectionId;
		this.listHeaderId = options.listHeaderId;
		this.listUlId = options.listUlId;
		this.listLiClass = options.listLiClass;

		this.getListHeaderHtml = options.getListHeaderHtml;
		this.getListLiHtml = options.getListLiHtml;

		// detail section
		this.detailSectionId = options.detailSectionId;
		this.detailHeaderId = options.detailHeaderId;
		this.detailArticleId = options.detailArticleId;
		this.detailEditArticleId = options.detailEditArticleId;

		this.getDetailArticleHtml = options.getDetailArticleHtml;
		this.getDetailEditArticleHtml = options.getDetailEditArticleHtml;

		// data attribute of each li
		this.listDataId = options.listDataId;

		// upload and download functions
		this.uploadItems = options.uploadItems;
		this.downloadItems = options.downloadItems;
	};

	// The 'new' keyword is not needed
	// because it is used inside SortableList constructor function
	SortableList.create.prototype = SortableList.prototype;

	window.SortableList = SortableList;

}(window, $));
