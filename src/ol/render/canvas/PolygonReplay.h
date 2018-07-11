/**
 * @module ol/render/canvas/PolygonReplay
 */
import {inherits} from '../../util.js';
import {asString} from '../../color.js';
import {snap} from '../../geom/flat/simplify.js';
import {defaultFillStyle} from '../canvas.js';
import CanvasInstruction, {
  fillInstruction, strokeInstruction, beginPathInstruction, closePathInstruction
} from '../canvas/Instruction.js';
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
const CanvasPolygonReplay = function(
  tolerance, maxExtent, resolution, pixelRatio, overlaps, declutterTree) {
  CanvasReplay.call(this,
    tolerance, maxExtent, resolution, pixelRatio, overlaps, declutterTree);
};

inherits(CanvasPolygonReplay, CanvasReplay);


/**
 * @param {Array.<number>} flatCoordinates Flat coordinates.
 * @param {number} offset Offset.
 * @param {Array.<number>} ends Ends.
 * @param {number} stride Stride.
 * @private
 * @return {number} End.
 */
CanvasPolygonReplay.prototype.drawFlatCoordinatess_ = function(flatCoordinates, offset, ends, stride) {
  const state = this.state;
  const fill = state.fillStyle !== undefined;
  const stroke = state.strokeStyle != undefined;
  const numEnds = ends.length;
  this.instructions.push(beginPathInstruction);
  this.hitDetectionInstructions.push(beginPathInstruction);
  for (let i = 0; i < numEnds; ++i) {
    const end = ends[i];
    const myBegin = this.coordinates.length;
    const myEnd = this.appendFlatCoordinates(flatCoordinates, offset, end, stride, true, !stroke);
    const moveToLineToInstruction = [CanvasInstruction.MOVE_TO_LINE_TO, myBegin, myEnd];
    this.instructions.push(moveToLineToInstruction);
    this.hitDetectionInstructions.push(moveToLineToInstruction);
    if (stroke) {
      // Performance optimization: only call closePath() when we have a stroke.
      // Otherwise the ring is closed already (see appendFlatCoordinates above).
      this.instructions.push(closePathInstruction);
      this.hitDetectionInstructions.push(closePathInstruction);
    }
    offset = end;
  }
  if (fill) {
    this.instructions.push(fillInstruction);
    this.hitDetectionInstructions.push(fillInstruction);
  }
  if (stroke) {
    this.instructions.push(strokeInstruction);
    this.hitDetectionInstructions.push(strokeInstruction);
  }
  return offset;
};


/**
 * @inheritDoc
 */
CanvasPolygonReplay.prototype.drawCircle = function(circleGeometry, feature) {
  const state = this.state;
  const fillStyle = state.fillStyle;
  const strokeStyle = state.strokeStyle;
  if (fillStyle === undefined && strokeStyle === undefined) {
    return;
  }
  this.setFillStrokeStyles_(circleGeometry);
  this.beginGeometry(circleGeometry, feature);
  if (state.fillStyle !== undefined) {
    this.hitDetectionInstructions.push([
      CanvasInstruction.SET_FILL_STYLE,
      asString(defaultFillStyle)
    ]);
  }
  if (state.strokeStyle !== undefined) {
    this.hitDetectionInstructions.push([
      CanvasInstruction.SET_STROKE_STYLE,
      state.strokeStyle, state.lineWidth, state.lineCap, state.lineJoin,
      state.miterLimit, state.lineDash, state.lineDashOffset
    ]);
  }
  const flatCoordinates = circleGeometry.getFlatCoordinates();
  const stride = circleGeometry.getStride();
  const myBegin = this.coordinates.length;
  this.appendFlatCoordinates(
    flatCoordinates, 0, flatCoordinates.length, stride, false, false);
  const circleInstruction = [CanvasInstruction.CIRCLE, myBegin];
  this.instructions.push(beginPathInstruction, circleInstruction);
  this.hitDetectionInstructions.push(beginPathInstruction, circleInstruction);
  this.hitDetectionInstructions.push(fillInstruction);
  if (state.fillStyle !== undefined) {
    this.instructions.push(fillInstruction);
  }
  if (state.strokeStyle !== undefined) {
    this.instructions.push(strokeInstruction);
    this.hitDetectionInstructions.push(strokeInstruction);
  }
  this.endGeometry(circleGeometry, feature);
};


/**
 * @inheritDoc
 */
CanvasPolygonReplay.prototype.drawPolygon = function(polygonGeometry, feature) {
  const state = this.state;
  const fillStyle = state.fillStyle;
  const strokeStyle = state.strokeStyle;
  if (fillStyle === undefined && strokeStyle === undefined) {
    return;
  }
  this.setFillStrokeStyles_(polygonGeometry);
  this.beginGeometry(polygonGeometry, feature);
  if (state.fillStyle !== undefined) {
    this.hitDetectionInstructions.push([
      CanvasInstruction.SET_FILL_STYLE,
      asString(defaultFillStyle)
    ]);
  }
  if (state.strokeStyle !== undefined) {
    this.hitDetectionInstructions.push([
      CanvasInstruction.SET_STROKE_STYLE,
      state.strokeStyle, state.lineWidth, state.lineCap, state.lineJoin,
      state.miterLimit, state.lineDash, state.lineDashOffset
    ]);
  }
  const ends = polygonGeometry.getEnds();
  const flatCoordinates = polygonGeometry.getOrientedFlatCoordinates();
  const stride = polygonGeometry.getStride();
  this.drawFlatCoordinatess_(flatCoordinates, 0, ends, stride);
  this.endGeometry(polygonGeometry, feature);
};


/**
 * @inheritDoc
 */
CanvasPolygonReplay.prototype.drawMultiPolygon = function(multiPolygonGeometry, feature) {
  const state = this.state;
  const fillStyle = state.fillStyle;
  const strokeStyle = state.strokeStyle;
  if (fillStyle === undefined && strokeStyle === undefined) {
    return;
  }
  this.setFillStrokeStyles_(multiPolygonGeometry);
  this.beginGeometry(multiPolygonGeometry, feature);
  if (state.fillStyle !== undefined) {
    this.hitDetectionInstructions.push([
      CanvasInstruction.SET_FILL_STYLE,
      asString(defaultFillStyle)
    ]);
  }
  if (state.strokeStyle !== undefined) {
    this.hitDetectionInstructions.push([
      CanvasInstruction.SET_STROKE_STYLE,
      state.strokeStyle, state.lineWidth, state.lineCap, state.lineJoin,
      state.miterLimit, state.lineDash, state.lineDashOffset
    ]);
  }
  const endss = multiPolygonGeometry.getEndss();
  const flatCoordinates = multiPolygonGeometry.getOrientedFlatCoordinates();
  const stride = multiPolygonGeometry.getStride();
  let offset = 0;
  for (let i = 0, ii = endss.length; i < ii; ++i) {
    offset = this.drawFlatCoordinatess_(flatCoordinates, offset, endss[i], stride);
  }
  this.endGeometry(multiPolygonGeometry, feature);
};


/**
 * @inheritDoc
 */
CanvasPolygonReplay.prototype.finish = function() {
  this.reverseHitDetectionInstructions();
  this.state = null;
  // We want to preserve topology when drawing polygons.  Polygons are
  // simplified using quantization and point elimination. However, we might
  // have received a mix of quantized and non-quantized geometries, so ensure
  // that all are quantized by quantizing all coordinates in the batch.
  const tolerance = this.tolerance;
  if (tolerance !== 0) {
    const coordinates = this.coordinates;
    for (let i = 0, ii = coordinates.length; i < ii; ++i) {
      coordinates[i] = snap(coordinates[i], tolerance);
    }
  }
};


/**
 * @private
 * @param {module:ol/geom/Geometry|module:ol/render/Feature} geometry Geometry.
 */
CanvasPolygonReplay.prototype.setFillStrokeStyles_ = function(geometry) {
  const state = this.state;
  const fillStyle = state.fillStyle;
  if (fillStyle !== undefined) {
    this.updateFillStyle(state, this.createFill, geometry);
  }
  if (state.strokeStyle !== undefined) {
    this.updateStrokeStyle(state, this.applyStroke);
  }
};
export default CanvasPolygonReplay;
