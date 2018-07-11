/**
 * @module ol/render/canvas/ImageReplay
 */
import {inherits} from '../../util.js';
import CanvasInstruction from '../canvas/Instruction.js';
import CanvasReplay from '../canvas/Replay.js';

/**
 * @constructor
 * @extends {module:ol/render/canvas/Replay}
 * @param {number} tolerance Tolerance.
 * @param {module:ol/extent~Extent} maxExtent Maximum extent.
 * @param {number} resolution Resolution.
 * @param {number} pixelRatio Pixel ratio.
 * @param {boolean} overlaps The replay can have overlapping geometries.
 * @param {?} declutterTree Declutter tree.
 * @struct
 */
const CanvasImageReplay = function(
  tolerance, maxExtent, resolution, pixelRatio, overlaps, declutterTree) {
  CanvasReplay.call(this,
    tolerance, maxExtent, resolution, pixelRatio, overlaps, declutterTree);

  /**
   * @private
   * @type {module:ol/render/canvas~DeclutterGroup}
   */
  this.declutterGroup_ = null;

  /**
   * @private
   * @type {HTMLCanvasElement|HTMLVideoElement|Image}
   */
  this.hitDetectionImage_ = null;

  /**
   * @private
   * @type {HTMLCanvasElement|HTMLVideoElement|Image}
   */
  this.image_ = null;

  /**
   * @private
   * @type {number|undefined}
   */
  this.anchorX_ = undefined;

  /**
   * @private
   * @type {number|undefined}
   */
  this.anchorY_ = undefined;

  /**
   * @private
   * @type {number|undefined}
   */
  this.height_ = undefined;

  /**
   * @private
   * @type {number|undefined}
   */
  this.opacity_ = undefined;

  /**
   * @private
   * @type {number|undefined}
   */
  this.originX_ = undefined;

  /**
   * @private
   * @type {number|undefined}
   */
  this.originY_ = undefined;

  /**
   * @private
   * @type {boolean|undefined}
   */
  this.rotateWithView_ = undefined;

  /**
   * @private
   * @type {number|undefined}
   */
  this.rotation_ = undefined;

  /**
   * @private
   * @type {number|undefined}
   */
  this.scale_ = undefined;

  /**
   * @private
   * @type {boolean|undefined}
   */
  this.snapToPixel_ = undefined;

  /**
   * @private
   * @type {number|undefined}
   */
  this.width_ = undefined;

};

inherits(CanvasImageReplay, CanvasReplay);


/**
 * @param {Array.<number>} flatCoordinates Flat coordinates.
 * @param {number} offset Offset.
 * @param {number} end End.
 * @param {number} stride Stride.
 * @private
 * @return {number} My end.
 */
CanvasImageReplay.prototype.drawCoordinates_ = function(flatCoordinates, offset, end, stride) {
  return this.appendFlatCoordinates(flatCoordinates, offset, end, stride, false, false);
};


/**
 * @inheritDoc
 */
CanvasImageReplay.prototype.drawPoint = function(pointGeometry, feature) {
  if (!this.image_) {
    return;
  }
  this.beginGeometry(pointGeometry, feature);
  const flatCoordinates = pointGeometry.getFlatCoordinates();
  const stride = pointGeometry.getStride();
  const myBegin = this.coordinates.length;
  const myEnd = this.drawCoordinates_(flatCoordinates, 0, flatCoordinates.length, stride);
  this.instructions.push([
    CanvasInstruction.DRAW_IMAGE, myBegin, myEnd, this.image_,
    // Remaining arguments to DRAW_IMAGE are in alphabetical order
    this.anchorX_, this.anchorY_, this.declutterGroup_, this.height_, this.opacity_,
    this.originX_, this.originY_, this.rotateWithView_, this.rotation_,
    this.scale_ * this.pixelRatio, this.snapToPixel_, this.width_
  ]);
  this.hitDetectionInstructions.push([
    CanvasInstruction.DRAW_IMAGE, myBegin, myEnd, this.hitDetectionImage_,
    // Remaining arguments to DRAW_IMAGE are in alphabetical order
    this.anchorX_, this.anchorY_, this.declutterGroup_, this.height_, this.opacity_,
    this.originX_, this.originY_, this.rotateWithView_, this.rotation_,
    this.scale_, this.snapToPixel_, this.width_
  ]);
  this.endGeometry(pointGeometry, feature);
};


/**
 * @inheritDoc
 */
CanvasImageReplay.prototype.drawMultiPoint = function(multiPointGeometry, feature) {
  if (!this.image_) {
    return;
  }
  this.beginGeometry(multiPointGeometry, feature);
  const flatCoordinates = multiPointGeometry.getFlatCoordinates();
  const stride = multiPointGeometry.getStride();
  const myBegin = this.coordinates.length;
  const myEnd = this.drawCoordinates_(
    flatCoordinates, 0, flatCoordinates.length, stride);
  this.instructions.push([
    CanvasInstruction.DRAW_IMAGE, myBegin, myEnd, this.image_,
    // Remaining arguments to DRAW_IMAGE are in alphabetical order
    this.anchorX_, this.anchorY_, this.declutterGroup_, this.height_, this.opacity_,
    this.originX_, this.originY_, this.rotateWithView_, this.rotation_,
    this.scale_ * this.pixelRatio, this.snapToPixel_, this.width_
  ]);
  this.hitDetectionInstructions.push([
    CanvasInstruction.DRAW_IMAGE, myBegin, myEnd, this.hitDetectionImage_,
    // Remaining arguments to DRAW_IMAGE are in alphabetical order
    this.anchorX_, this.anchorY_, this.declutterGroup_, this.height_, this.opacity_,
    this.originX_, this.originY_, this.rotateWithView_, this.rotation_,
    this.scale_, this.snapToPixel_, this.width_
  ]);
  this.endGeometry(multiPointGeometry, feature);
};


/**
 * @inheritDoc
 */
CanvasImageReplay.prototype.finish = function() {
  this.reverseHitDetectionInstructions();
  // FIXME this doesn't really protect us against further calls to draw*Geometry
  this.anchorX_ = undefined;
  this.anchorY_ = undefined;
  this.hitDetectionImage_ = null;
  this.image_ = null;
  this.height_ = undefined;
  this.scale_ = undefined;
  this.opacity_ = undefined;
  this.originX_ = undefined;
  this.originY_ = undefined;
  this.rotateWithView_ = undefined;
  this.rotation_ = undefined;
  this.snapToPixel_ = undefined;
  this.width_ = undefined;
};


/**
 * @inheritDoc
 */
CanvasImageReplay.prototype.setImageStyle = function(imageStyle, declutterGroup) {
  const anchor = imageStyle.getAnchor();
  const size = imageStyle.getSize();
  const hitDetectionImage = imageStyle.getHitDetectionImage(1);
  const image = imageStyle.getImage(1);
  const origin = imageStyle.getOrigin();
  this.anchorX_ = anchor[0];
  this.anchorY_ = anchor[1];
  this.declutterGroup_ = /** @type {module:ol/render/canvas~DeclutterGroup} */ (declutterGroup);
  this.hitDetectionImage_ = hitDetectionImage;
  this.image_ = image;
  this.height_ = size[1];
  this.opacity_ = imageStyle.getOpacity();
  this.originX_ = origin[0];
  this.originY_ = origin[1];
  this.rotateWithView_ = imageStyle.getRotateWithView();
  this.rotation_ = imageStyle.getRotation();
  this.scale_ = imageStyle.getScale();
  this.snapToPixel_ = imageStyle.getSnapToPixel();
  this.width_ = size[0];
};
export default CanvasImageReplay;
